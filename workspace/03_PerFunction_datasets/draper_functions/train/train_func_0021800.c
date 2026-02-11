rsakey_pubblob(const Filename *filename, void **blob, int *bloblen,
		   char **commentptr, const char **errorstr)
{
    FILE *fp;
    char buf[64];
    struct RSAKey key;
    int ret;
    const char *error = NULL;


    *blob = NULL;
    *bloblen = 0;
    ret = 0;

    fp = f_open(*filename, "rb", FALSE);
    if (!fp) {
	error = "can't open file";
	goto end;
    }


    if (fgets(buf, sizeof(buf), fp) && !strcmp(buf, rsa_signature)) {
	memset(&key, 0, sizeof(key));
	if (loadrsakey_main(fp, &key, TRUE, commentptr, NULL, &error)) {
	    *blob = rsa_public_blob(&key, bloblen);
	    freersakey(&key);
	    ret = 1;
	    fp = NULL;
	}
    } else {
	error = "not an SSH-1 RSA file";
    }

  end:
    if (fp)
	fclose(fp);
    if ((ret != 1) && errorstr)
	*errorstr = error;
    return ret;
}

FcHashGetSHA256DigestFromFile (const FcChar8 *filename)
{
    FILE *fp = fopen ((const char *)filename, "rb");
    char ibuf[64];
    FcChar32 *ret;
    size_t len;
    struct stat st;

    if (!fp)
	return NULL;

    if (FcStat (filename, &st))
	goto bail0;

    ret = FcHashInitSHA256Digest ();
    if (!ret)
	goto bail0;

    while (!feof (fp))
    {
	if ((len = fread (ibuf, sizeof (char), 64, fp)) < 64)
	{
	    long v;


	    memset (&ibuf[len], 0, 64 - len);
	    ibuf[len] = 0x80;
	    if ((64 - len) < 9)
	    {

		FcHashComputeSHA256Digest (ret, ibuf);
		memset (ibuf, 0, 64);
	    }

	    v = (long)st.st_size * 8;
	    ibuf[63 - 0] =  v        & 0xff;
	    ibuf[63 - 1] = (v >>  8) & 0xff;
	    ibuf[63 - 2] = (v >> 16) & 0xff;
	    ibuf[63 - 3] = (v >> 24) & 0xff;
	    ibuf[63 - 4] = (v >> 32) & 0xff;
	    ibuf[63 - 5] = (v >> 40) & 0xff;
	    ibuf[63 - 6] = (v >> 48) & 0xff;
	    ibuf[63 - 7] = (v >> 56) & 0xff;
	    FcHashComputeSHA256Digest (ret, ibuf);
	    break;
	}
	else
	{
	    FcHashComputeSHA256Digest (ret, ibuf);
	}
    }
    fclose (fp);

    return FcHashSHA256ToString (ret);

bail0:
    fclose (fp);

    return NULL;
}

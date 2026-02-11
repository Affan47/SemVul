dst_s_write_private_key(const DST_KEY *key)
{
	u_char encoded_block[RAW_KEY_SIZE];
	char file[PATH_MAX];
	int len;
	FILE *fp;


	if (key == NULL)
		return (-1);
	if (key->dk_KEY_struct == NULL)
		return (0);
	if (key->dk_func == NULL || key->dk_func->to_file_fmt == NULL) {
		EREPORT(("dst_write_private_key(): Unsupported operation %d\n",
			 key->dk_alg));
		return (-5);
	} else if ((len = key->dk_func->to_file_fmt(key, (char *)encoded_block,
					     sizeof(encoded_block))) <= 0) {
		EREPORT(("dst_write_private_key(): Failed encoding private RSA bsafe key %d\n", len));
		return (-8);
	}

	dst_s_build_filename(file, key->dk_key_name, key->dk_id, key->dk_alg,
			     PRIVATE_KEY, PATH_MAX);


	if ((fp = dst_s_fopen(file, "w", 0600)) != NULL) {
		int nn;
		if ((nn = fwrite(encoded_block, 1, len, fp)) != len) {
			EREPORT(("dst_write_private_key(): Write failure on %s %d != %d errno=%d\n",
				 file, len, nn, errno));
			fclose(fp);
			return (-5);
		}
		fclose(fp);
	} else {
		EREPORT(("dst_write_private_key(): Can not create file %s\n"
			 ,file));
		return (-6);
	}
	memset(encoded_block, 0, len);
	return (len);
}

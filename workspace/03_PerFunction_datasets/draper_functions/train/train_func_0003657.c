save_ts_serial(const char *serialfile, ASN1_INTEGER *serial)
	{
	int ret = 0;
	BIO *out = NULL;

	if (!(out = BIO_new_file(serialfile, "w"))) goto err;
	if (i2a_ASN1_INTEGER(out, serial) <= 0) goto err;
	if (BIO_puts(out, "\n") <= 0) goto err;
	ret = 1;
 err:
	if (!ret)
		BIO_printf(bio_err, "could not save serial number to %s\n",
			   serialfile);
	BIO_free_all(out);
	return ret;
	}

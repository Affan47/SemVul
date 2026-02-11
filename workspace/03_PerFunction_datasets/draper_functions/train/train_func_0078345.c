NCONF_load_bio(CONF *conf, BIO *bp,long *eline)
	{
	if (conf == NULL)
		{
		CONFerr(CONF_F_NCONF_LOAD_BIO,CONF_R_NO_CONF);
		return 0;
		}

	return conf->meth->load_bio(conf, bp, eline);
	}

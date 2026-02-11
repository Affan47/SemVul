load_config_file(const char *configfile)
	{
	CONF *conf = NULL;
	long errorline = -1;

	if (!configfile) configfile = getenv("OPENSSL_CONF");
	if (!configfile) configfile = getenv("SSLEAY_CONF");

	if (configfile &&
	    (!(conf = NCONF_new(NULL)) ||
	     NCONF_load(conf, configfile, &errorline) <= 0))
		{
		if (errorline <= 0)
			BIO_printf(bio_err, "error loading the config file "
				   "'%s'\n", configfile);
		else
			BIO_printf(bio_err, "error on line %ld of config file "
				   "'%s'\n", errorline, configfile);
		}

	if (conf != NULL)
		{
		const char *p;

		BIO_printf(bio_err,"Using configuration from %s\n", configfile);
		p = NCONF_get_string(conf, NULL, ENV_OID_FILE);
		if (p != NULL)
			{
			BIO *oid_bio = BIO_new_file(p, "r");
			if (!oid_bio)
				ERR_print_errors(bio_err);
			else
				{
				OBJ_create_objects(oid_bio);
				BIO_free_all(oid_bio);
				}
			}
		else
			ERR_clear_error();
		if(!add_oid_section(bio_err, conf))
			ERR_print_errors(bio_err);
		}
	return conf;
	}

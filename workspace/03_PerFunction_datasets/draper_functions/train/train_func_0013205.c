setup_cryptcmd(phost_t host)
{


	char *crypt;

	if ( strcasecmp(host->alg, GPG_ALG) == 0 ) {


		crypt = g_strdup_printf("%s " GPG_CRYPT ,
			host->gpg,
			host->keypath);

		LOGDEBUG("%s\n",crypt);

	} else {

		crypt = g_strdup_printf("%s -u -q -a %s -f %s",
			host->mcrypt,
			host->alg,
			host->keypath);
	}


	if ( quiet > 0 ) {

		crypt = g_strconcat(crypt, MUTE, NULL);
	}

	return crypt;
}

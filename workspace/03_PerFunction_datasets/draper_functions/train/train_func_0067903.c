setup_decryptcmd(phost_t host)
{


	char *crypt;

	if ( strcasecmp(host->alg, GPG_ALG) == 0 ) {


		crypt = g_strdup_printf("%s " GPG_DECRYPT ,
			host->gpg,
			host->keypath);
	} else {

		crypt = g_strdup_printf("%s -d -q -a %s -f %s",
			host->mcrypt,
			host->alg,
			host->keypath);
	}

	LOGDEBUG("%s\n",crypt);


	if ( quiet > 0 ) {

		crypt = g_strconcat(crypt, MUTE, NULL);
	}


	return crypt;
}

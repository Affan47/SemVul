maclist_reload(void){
	int retval;

	#ifdef DEBUG
	logmsg(LOG_DEBUG, "[%s %d %s] reload maclist",
	       __FILE__, __LINE__, __FUNCTION__);
	#endif


	if(config[CF_MACLIST].valeur.string != NULL &&
	   config[CF_MACLIST].valeur.string[0] != 0){
		retval = maclist_file(config[CF_MACLIST].valeur.string,
		                        ALLOW, TEST);
		if(retval == -1){
			logmsg(LOG_ERR,
			       "errors in file \"%s\": not reload",
			       config[CF_MACLIST].valeur.string);
			return;
		}
	}


	if(config[CF_BLACKLST].valeur.string != NULL &&
	   config[CF_BLACKLST].valeur.string[0] != 0){
		retval = maclist_file(config[CF_BLACKLST].valeur.string,
		                       DENY, TEST);
		if(retval == -1){
			logmsg(LOG_ERR,
			       "errors in file \"%s\": not reload",
			       config[CF_MACLIST].valeur.string);
			return;
		}
	}


	if(config[CF_MACLIST].valeur.string != NULL &&
	   config[CF_MACLIST].valeur.string[0] != 0){
		retval = maclist_file(config[CF_MACLIST].valeur.string,
		                      ALLOW, RELOAD);
		if(retval == -1){
			exit(1);
		}
	}


	if(config[CF_BLACKLST].valeur.string != NULL &&
	   config[CF_BLACKLST].valeur.string[0] != 0){
		retval = maclist_file(config[CF_BLACKLST].valeur.string,
		                      DENY, RELOAD);
		if(retval == -1){
			exit(1);
		}
	}
}

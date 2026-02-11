connect( pfs_name *name ) {

		struct ftp_lite_server *server = NULL;
		int result = 0;
		int save_errno;

		debug(D_FTP,"connecting to %s:%d",name->host,name->port);

		if(this->type==GLOBUS_GSS) {
			server = ftp_lite_open(name->host,name->port);
			if(!server) return 0;
			result = ftp_lite_auth_globus(server);
		} else if(this->type==ANONYMOUS) {
			char username[USERNAME_MAX];
			char hostname[DOMAIN_NAME_MAX];
			char email[USERNAME_MAX+DOMAIN_NAME_MAX+1];
			if(!username_get(username)) strcpy(username,"anonymous");
			if(!domain_name_cache_guess(hostname)) strcpy(hostname,"nowhere");
			sprintf(email,"%s@%s",username,hostname);
			server = ftp_lite_open(name->host,name->port);
			if(!server) return 0;
			result = ftp_lite_auth_userpass(server,"anonymous",email);
		} else if(this->type==USERPASS) {
			char user[FTP_LITE_LINE_MAX];
			char pass[FTP_LITE_LINE_MAX];

			if(!strncmp(name->host,"anonymous@",10)) {
				server = ftp_lite_open(name->host+10,name->port);
				if(!server) return 0;
				result = ftp_lite_auth_userpass(server,"anonymous","anonymous");
			} else {
				server = ftp_lite_open(name->host,name->port);
				if(!server) return 0;
				if(!ftp_lite_login(name->host,user,FTP_LITE_LINE_MAX,pass,FTP_LITE_LINE_MAX)) {
					memset(pass,0,FTP_LITE_LINE_MAX);
					ftp_lite_close(server);
					errno = EACCES;
					return 0;
				}
				result = ftp_lite_auth_userpass(server,user,pass);
				memset(pass,0,FTP_LITE_LINE_MAX);
			}
		}

		if(!result) {
			save_errno = errno;
			debug(D_FTP,"couldn't authenticate to %s:%d: %s",name->host,name->port,strerror(errno));
			ftp_lite_close(server);
			errno = save_errno;
			return 0;
		} else {
			return (void*) server;
		}
	}

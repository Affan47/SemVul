growl( const char *const server,const char *const appname,const char *const notify,const char *const title, const char *const message ,
                                const char *const icon , const char *const password , const char *url )
{
	int rc = growl_tcp_register(  server ,  appname ,  (const char **const)&notify , 1 , password, icon  );
	if( rc == 0 )
	{
		rc = growl_tcp_notify( server, appname, notify, title,  message , password, url, icon );
	}
	return rc;
}

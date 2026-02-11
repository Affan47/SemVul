_init_system_name() {
  char *  host   = NULL;
  char *  domain = NULL;
  char *  ptr    = NULL;
  char ** hdout  = NULL;
  int     rc     = 0;

  if( !CIM_HOST_NAME ) {

    _OSBASE_TRACE(4,("--- _init_system_name() called : init"));

    host = calloc(1,255);
    if ( gethostname(host, 255 ) == -1 ) {
        _OSBASE_TRACE(4,("--- _init_system_name() : gethostname returned -1"));
    }


    if( strchr( host , '.') == NULL ) {

      rc=runcommand("/bin/dnsdomainname",NULL,&hdout,NULL);
      if (rc == 0 && hdout != NULL) {
	if (hdout[0]) {
	  domain = strdup(hdout[0]);
	  ptr = strchr(domain, '\n');
	  *ptr = '\0';
	}
	freeresultbuf(hdout);
      }
    }


    if( strlen(host) ) {
      if( !domain ) {
	CIM_HOST_NAME = calloc(1,(strlen(host)+1));
	strcpy( CIM_HOST_NAME, host);
      }
      else {
	CIM_HOST_NAME = calloc(1,(strlen(host)+strlen(domain)+2));
	strcpy( CIM_HOST_NAME, host);
	strcat( CIM_HOST_NAME, ".");
	strcat( CIM_HOST_NAME, domain );
      }
    } else {
        CIM_HOST_NAME = calloc(1, (strlen(DEFAULT_HOST_NAME) + 1));
        strcpy(CIM_HOST_NAME, DEFAULT_HOST_NAME);
    }

    if(host) free(host);
    if(domain) free(domain);

    _OSBASE_TRACE(4,("--- _init_system_name() : CIM_HOST_NAME initialized with %s",CIM_HOST_NAME));
  }

}

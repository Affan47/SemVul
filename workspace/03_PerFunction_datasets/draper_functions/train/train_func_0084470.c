show_config( int EXIT )
{
  char *method;
  switch (my.method) {
    case GET:
      method = strdup("GET");
      break;
    case HEAD:
    default:
      method = strdup("HEAD");
      break;
  }

  printf( "CURRENT  SIEGE  CONFIGURATION\n" );
  printf( "%s\n", my.uagent );
  printf( "Edit the resource file to change the settings.\n" );
  printf( "----------------------------------------------\n" );
  printf( "version:                        %s\n", version_string );
  printf( "verbose:                        %s\n", my.verbose?"true":"false" );
  printf( "quiet:                          %s\n", my.quiet?"true":"false" );
  printf( "debug:                          %s\n", my.debug?"true":"false" );
  printf( "protocol:                       %s\n", my.protocol?"HTTP/1.1":"HTTP/1.0" );
  printf( "get method:                     %s\n", method);
  if (auth_get_proxy_required(my.auth)){
    printf("proxy-host:                     %s\n", auth_get_proxy_host(my.auth));
    printf("proxy-port:                     %d\n", auth_get_proxy_port(my.auth));
  }
  printf( "connection:                     %s\n", my.keepalive?"keep-alive":"close" );
  printf( "concurrent users:               %d\n", my.cusers );
  if( my.secs > 0 )
    printf( "time to run:                    %d seconds\n", my.secs );
  else
    printf( "time to run:                    n/a\n" );
  if(( my.reps > 0 )&&( my.reps != MAXREPS ))
    printf( "repetitions:                    %d\n", my.reps );
  else
    printf( "repetitions:                    n/a\n" );
  printf( "socket timeout:                 %d\n", my.timeout );
  printf( "delay:                          %d sec%s\n", my.delay,my.delay>1?"s":"" );
  printf( "internet simulation:            %s\n", my.internet?"true":"false"  );
  printf( "benchmark mode:                 %s\n", my.bench?"true":"false"  );
  printf( "failures until abort:           %d\n", my.failures );
  printf( "named URL:                      %s\n", my.url==NULL||strlen(my.url)<2?"none":my.url );
  printf( "URLs file:                      %s\n", strlen(my.file)>1?my.file:URL_FILE );
  printf( "logging:                        %s\n", my.logging?"true":"false" );
  printf( "log file:                       %s\n", my.logfile==NULL?LOG_FILE:my.logfile );
  printf( "resource file:                  %s\n", my.rc);
  printf( "timestamped output:             %s\n", my.timestamp?"true":"false");
  printf( "comma separated output:         %s\n", my.csv?"true":"false");
  printf( "allow redirects:                %s\n", my.follow?"true":"false" );
  printf( "allow zero byte data:           %s\n", my.zero_ok?"true":"false" );
  printf( "allow chunked encoding:         %s\n", my.chunked?"true":"false" );
  printf( "upload unique files:            %s\n", my.unique?"true":"false" );


  printf( "\n" );
  xfree(method);
  if (EXIT) exit(0);
  else return 0;
}

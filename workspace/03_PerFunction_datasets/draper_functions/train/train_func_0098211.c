Initialize_steering_connection(int  NumSupportedCmds,
				   int *SupportedCmds)
{
  char *pchar;
  int   interval, i;


  Steerer_connection.polling_interval = REG_APP_POLL_INTERVAL_DEFAULT;

  if( (pchar = getenv("REG_APP_POLL_INTERVAL")) ){

    if(sscanf(pchar, "%d", &interval) == 1){

      Steerer_connection.polling_interval = (double)interval;
    }
  }


  for(i=0; i<NumSupportedCmds; i++){
    if(SupportedCmds[i] == REG_STR_PAUSE_INTERNAL){
      Steerer_connection.handle_pause_cmd = REG_TRUE;
      SupportedCmds[i] = REG_STR_PAUSE;
      break;
    }
  }

#ifdef REG_DEBUG
  fprintf(stderr, "STEER: Initialize_steering_connection: polling "
	  "interval = %d\n", (int)Steerer_connection.polling_interval);
#endif


  return Initialize_steering_connection_impl(NumSupportedCmds,
					     SupportedCmds);
}

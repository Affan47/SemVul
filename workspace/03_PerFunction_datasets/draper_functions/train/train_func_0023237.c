OpStart()
{
   dac_start_ot out ;

   if (start_flag == YES)
    {
       out.status = htons(FAILURE) ;
       out.error = htons(DAC_ER_STARTED) ;
    }
   else if (!execAllHandlers())
    {
       out.status = htons(FAILURE) ;
       out.error = htons(DAC_ER_EXECHANDLER) ;
    }
   else
    {
       start_flag = YES ;
       execReadyProcesses() ;
       out.status = htons(SUCCESS) ;
       out.error = htons(DAC_ER_NOERROR) ;
    }
   if (debug) printf("DAC startup status (%d) \n",out.error);
   writen(newsock, (char *)&out, sizeof(dac_start_ot)) ;
   if (process_list == NULL)
   {
   	send_cid_appstatus(hostname, APP_EXITTED);
	if (debug) printf(" Process list empty. Exiting ...\n");
	exit(1);
   }
   send_cid_appstatus(hostname, APP_RUNNING);
}

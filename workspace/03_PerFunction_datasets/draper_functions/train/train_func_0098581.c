snmp_collator_stop()
{
	int err;

	if (snmp_collator_stopped) {
		return 0;
	}


	slapi_eq_cancel(snmp_eq_ctx);
	snmp_collator_stopped = 1;


   snmp_collator_sem_wait();


   if ((err = agt_mclose_stats(hdl)) != 0)
   {
        fprintf(stderr, "Failed to close stats file (%s) (error = %d).",
            AGT_STATS_FILE, err);
   }

   if (remove(tmpstatsfile) != 0)
   {
       fprintf(stderr, "Failed to remove (%s) (error =  %d).\n",
            tmpstatsfile, errno);
   }


   sem_close(stats_sem);
   sem_unlink(stats_sem_name);


   if (interaction_table_mutex) {
       PR_DestroyLock(interaction_table_mutex);
   }

#ifdef _WIN32

   sc_setevent(MAGT_NSEV_SNMPTRAP);

#endif


return 0;
}

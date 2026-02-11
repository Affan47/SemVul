reload_config(int sig)
{
   static bool already_here = false;
#if !defined(HAVE_WIN32)
   sigset_t set;
#endif
   JCR *jcr;
   int njobs = 0;
   int table, rtable;
   bool ok;

   if (already_here) {
      abort();
   }
   already_here = true;

#if !defined(HAVE_WIN32)
   sigemptyset(&set);
   sigaddset(&set, SIGHUP);
   sigprocmask(SIG_BLOCK, &set, NULL);
#endif

   lock_jobs();
   LockRes();

   table = find_free_reload_table_entry();
   if (table < 0) {
      Jmsg(NULL, M_ERROR, 0, _("Too many open reload requests. Request ignored.\n"));
      goto bail_out;
   }

   Dmsg1(100, "Reload_config njobs=%d\n", njobs);
   reload_table[table].res_table = config->save_resources();
   Dmsg1(100, "Saved old config in table %d\n", table);

   ok = parse_dir_config(config, configfile, M_ERROR);

   Dmsg0(100, "Reloaded config file\n");
   if (!ok || !check_resources() || !check_catalog(UPDATE_CATALOG)) {
      rtable = find_free_reload_table_entry();
      if (rtable < 0) {
         Jmsg(NULL, M_ERROR, 0, _("Please correct configuration file: %s\n"), configfile);
         Jmsg(NULL, M_ERROR_TERM, 0, _("Out of reload table entries. Giving up.\n"));
      } else {
         Jmsg(NULL, M_ERROR, 0, _("Please correct configuration file: %s\n"), configfile);
         Jmsg(NULL, M_ERROR, 0, _("Resetting previous configuration.\n"));
      }
      reload_table[rtable].res_table = config->save_resources();

      int num = r_last - r_first + 1;
      RES **res_tab = reload_table[table].res_table;
      for (int i=0; i<num; i++) {
         res_head[i] = res_tab[i];
      }
      table = rtable;
   } else {
      invalidate_schedules();


      foreach_jcr(jcr) {
         if (jcr->getJobType() != JT_SYSTEM) {
            reload_table[table].job_count++;
            job_end_push(jcr, reload_job_end_cb, (void *)((long int)table));
            njobs++;
         }
      }
      endeach_jcr(jcr);
   }


   set_working_directory(director->working_directory);
   FDConnectTimeout = director->FDConnectTimeout;
   SDConnectTimeout = director->SDConnectTimeout;
   Dmsg0(10, "Director's configuration file reread.\n");


   if (njobs == 0) {
      free_saved_resources(table);
   }

bail_out:
   UnlockRes();
   unlock_jobs();
#if !defined(HAVE_WIN32)
   sigprocmask(SIG_UNBLOCK, &set, NULL);
   signal(SIGHUP, reload_config);
#endif
   already_here = false;
}

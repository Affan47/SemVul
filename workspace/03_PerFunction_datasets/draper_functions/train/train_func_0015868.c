wizard_page_show(E_Wizard_Page *pg __UNUSED__)
{
   int hav_cpufreq = 0;
#ifdef __FreeBSD__
   char buf[PATH_MAX];
   size_t len = 0;

   len = sizeof(buf);
   if (sysctlbyname("dev.cpu.0.freq_levels", buf, &len, NULL, 0) == 0)
     hav_cpufreq = 1;
#else
   char *str, *p;

   str = read_file("/sys/devices/system/cpu/cpu0/cpufreq/scaling_available_frequencies");
   if (str)
     {
        for (p = str; *p; p++)
          {
             if (isspace(*p))
               {
                  hav_cpufreq = 1;
                  break;
               }
          }
        free(str);
     }
#endif
   if (!hav_cpufreq)
     {
        E_Config_Module *em;
        Eina_List *l;

        EINA_LIST_FOREACH(e_config->modules, l, em)
          {
             if (!em->name) continue;
             if (!strcmp(em->name, "cpufreq"))
               {
                  e_config->modules = eina_list_remove_list
                      (e_config->modules, l);
                  if (em->name) eina_stringshare_del(em->name);
                  free(em);
                  break;
               }
          }
        e_config_save_queue();
     }
   return 0;
}

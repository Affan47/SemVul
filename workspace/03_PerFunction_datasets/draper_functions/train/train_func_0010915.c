e_exehist_add(const char *launch_method, const char *exe)
{
   E_Exehist_Item *ei;

   _e_exehist_load();
   if (!_e_exehist) return;
   ei = E_NEW(E_Exehist_Item, 1);
   if (!ei)
     {
        _e_exehist_unload_queue();
        return;
     }
   ei->launch_method = eina_stringshare_add(launch_method);
   ei->exe = eina_stringshare_add(exe);
   ei->normalized_exe = _e_exehist_normalize_exe(exe);
   ei->exetime = ecore_time_unix_get();
   _e_exehist->history = eina_list_append(_e_exehist->history, ei);
   _e_exehist_limit();
   _e_exehist_changes++;
   ecore_event_add(E_EVENT_EXEHIST_UPDATE, NULL, NULL, NULL);
   _e_exehist_unload_queue();
}

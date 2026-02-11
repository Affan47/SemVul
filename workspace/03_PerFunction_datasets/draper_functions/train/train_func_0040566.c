reschedule_unknown_timeout(lListElem *hep)
{
   static int not_init = 1;
   u_long32 timeout = 0;
   const char *host = NULL;

   DENTER(TOP_LAYER, "reschedule_unknown_timeout");

   host = lGetHost(hep, EH_name);
   timeout = lGetUlong(hep, EH_reschedule_unknown);


   if (mconf_is_new_config() || not_init)
   {
      lListElem *conf_entry = NULL;

      if ((conf_entry = sge_get_configuration_entry_by_name(host, "reschedule_unknown")) != NULL)
      {
         if (parse_ulong_val(NULL, &timeout, TYPE_TIM, lGetString(conf_entry, CF_value), NULL, 0) == 0)
         {
            ERROR((SGE_EVENT, MSG_OBJ_RESCHEDULEUNKN_SS, host, lGetString(conf_entry, CF_value)));
            timeout = 0;
         }

         lFreeElem(&conf_entry);
      }

      DPRINTF(("%s: reschedule_unknown timeout for host %s is "sge_u32"\n", SGE_FUNC, host, timeout));

      lSetUlong(hep, EH_reschedule_unknown, timeout);

      not_init = 0;
   }

   DRETURN(timeout);
}

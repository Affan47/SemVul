_on_cmd_profile_set_offline_mode(__UNUSED__ char *cmd, char *args)
{
   char *path, *next_args;
   Eina_Bool offline;
   E_Connman_Element *e;

   if (!args)
     {
	fputs("ERROR: missing the profile path\n", stderr);
	return ECORE_CALLBACK_RENEW;
     }
   path = args;
   next_args = _tok(args);
   if (!next_args)
     {
	fputs("ERROR: missing the offline mode value\n", stderr);
	return ECORE_CALLBACK_RENEW;
     }
   _tok(next_args);
   offline = !!atol(next_args);

   e = e_connman_profile_get(path);
   if (e_connman_profile_offline_mode_set
       (e, offline, _method_success_check, "profile_set_offline_mode"))
     printf(":::Profile %s Offline Mode set to %hhu\n", path, offline);
   else
     fputs("ERROR: can't set profile offline mode\n", stderr);
   return ECORE_CALLBACK_RENEW;
}

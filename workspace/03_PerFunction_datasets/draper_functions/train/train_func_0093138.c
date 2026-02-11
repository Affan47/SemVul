_on_cmd_manager_register_agent(__UNUSED__ char *cmd, char *args)
{
   char *path;

   if (!args)
     {
	fputs("ERROR: missing the object path\n", stderr);
	return ECORE_CALLBACK_RENEW;
     }

   path = args;
   if (e_connman_manager_agent_register
       (path, _method_success_check, "manager_register_agent"))
     printf(":::Registering agent %s...\n", path);
   else
     fprintf(stderr, "ERROR: can't register agent %s\n", path);

   return ECORE_CALLBACK_RENEW;
}

_on_cmd_service_get_security(__UNUSED__ char *cmd, char *args)
{
   unsigned int count;
   const char **security;
   const char *path;
   E_Connman_Element *e;

   if (!args)
     {
	fputs("ERROR: missing the service path\n", stderr);
	return ECORE_CALLBACK_RENEW;
     }
   _tok(args);
   path = args;

   e = e_connman_service_get(path);
   if (e_connman_service_security_get(e, &count, &security))
     {
        unsigned int i;
        for (i = 0; i < count; i++)
          printf("\"%s\", ", security[i]);
        putchar('\n');
     }
   else
     fputs("ERROR: can't get service security\n", stderr);
   return ECORE_CALLBACK_RENEW;
}

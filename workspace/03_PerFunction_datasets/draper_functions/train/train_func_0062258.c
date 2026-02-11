_on_cmd_get_all(__UNUSED__ char *cmd, char *args)
{
   E_Bluez_Element **elements;
   char *type;
   unsigned int count;
   Eina_Bool ret;

   if (!args)
     type = NULL;
   else
     type = args;

   if (type)
     ret = e_bluez_elements_get_all_type(type, &count, &elements);
   else
     ret = e_bluez_elements_get_all(&count, &elements);

   if (!ret)
     fputs("ERROR: could not get elements\n", stderr);
   else
     {
	printf("BEG: all elements type=%s count = %d\n", type, count);
	_elements_print(elements, count);
     }

   return ECORE_CALLBACK_RENEW;
}

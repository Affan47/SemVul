_e_util_conf_timer_new(void *data)
{
   char *module_name = data;
   char buf[4096];
   char *msg =
     _("Your module configuration is NEWER "
       "than the module version. This is "
       "very<br>strange. This should not happen unless"
       " you downgraded<br>the module or "
       "copied the configuration from a place where"
       "<br>a newer version of the module "
       "was running. This is bad and<br>as a "
       "precaution your configuration has been now "
       "restored to<br>defaults. Sorry for the "
       "inconvenience.<br>");

   snprintf(buf, sizeof(buf), _("%s Configuration Updated"), module_name);
   e_util_dialog_internal(buf, msg);
   E_FREE(module_name);

   return ECORE_CALLBACK_CANCEL;
}

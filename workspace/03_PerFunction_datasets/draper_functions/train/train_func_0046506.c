_lc_check(void)
{
   char buf[8192];
   char buf2[512];
   E_Dialog *dia;

   buf2[0] = 0;

   if (getenv("LC_CTYPE")) strcat(buf2, "<br>LC_CTYPE");
   if (getenv("LC_NUMERIC")) strcat(buf2, "<br>LC_NUMERIC");
   if (getenv("LC_TIME")) strcat(buf2, "<br>LC_TIME");
   if (getenv("LC_COLLATE")) strcat(buf2, "<br>LC_COLLATE");
   if (getenv("LC_MONETARY")) strcat(buf2, "<br>LC_MONETARY");
   if (getenv("LC_MESSAGES")) strcat(buf2, "<br>LC_MESSAGES");
   if (getenv("LC_ALL")) strcat(buf2, "<br>LC_ALL");

   if (!buf2[0])
     {
        _lc_check_del(NULL);
        return;
     }

   snprintf(buf, sizeof(buf), _("You have some extra locale environment<br>"
                                 "variables set that may interfere with<br>"
                                 "correct display of your chosen language.<br>"
                                 "If you don't want these affected, use the<br>"
                                 "Environment variable settings to unset them.<br>"
                                 "The variables that may affect you are<br>"
                                 "as follows:<br>"
                                 "%s"), buf2);
   dia = e_util_dialog_internal(_("Possible Locale problems"), buf);
   e_object_free_attach_func_set(E_OBJECT(dia), _lc_check_del);
}

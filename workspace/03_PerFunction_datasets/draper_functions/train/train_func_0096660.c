_e_sys_logout_confirm_dialog_update(int remaining)
{
   char txt[4096];

   if (!_e_sys_logout_confirm_dialog)
     {
        fputs("ERROR: updating logout confirm dialog, but none exists!\n",
              stderr);
        return;
     }

   snprintf(txt, sizeof(txt),
            _("Logout is taking too long.<br>"
              "Some applications refuse to close.<br>"
              "Do you want to finish the logout<br>"
              "anyway without closing these<br>"
              "applications first?<br><br>"
              "Auto logout in %d seconds."), remaining);

   e_dialog_text_set(_e_sys_logout_confirm_dialog, txt);
}

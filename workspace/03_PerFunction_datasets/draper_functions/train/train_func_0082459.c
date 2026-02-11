dialer(gpointer data, int phone_or_ext)
{
   struct dialog_data *Pdata;
   char str[70];
   char null_str[]="";
   const char *Pext;
   char command[1024];
   const char *pref_command;
   char c1, c2;
   int i, len;

   Pdata=data;
   if (phone_or_ext==CHOOSE_PHONE) {
      g_snprintf(str, sizeof(str), "%s%s%s%s",
                 GTK_TOGGLE_BUTTON(Pdata->check_pre1)->active ?
                 gtk_entry_get_text(GTK_ENTRY(Pdata->entry_pre1)) : "",
                 GTK_TOGGLE_BUTTON(Pdata->check_pre2)->active ?
                 gtk_entry_get_text(GTK_ENTRY(Pdata->entry_pre2)) : "",
                 GTK_TOGGLE_BUTTON(Pdata->check_pre3)->active ?
                 gtk_entry_get_text(GTK_ENTRY(Pdata->entry_pre3)) : "",
                 gtk_entry_get_text(GTK_ENTRY(Pdata->entry_phone)));
   }
   if (phone_or_ext==CHOOSE_EXT) {
      Pext=gtk_entry_get_text(GTK_ENTRY(Pdata->entry_ext));
      if (!Pext) Pext=null_str;
      g_strlcpy(str, Pext, sizeof(str));
   }

   pref_command = gtk_entry_get_text(GTK_ENTRY(Pdata->entry_command));

   memset(command, 0, sizeof(command));
   for (i=0; i<MAX_PREF_LEN-1; i++) {
      c1 = pref_command[i];
      c2 = pref_command[i+1];
      len = strlen(command);

      if (c1=='%') {
         if (c2=='n') {
            i++;
            strncat(command, str, 1022-len);
            continue;
         }
      }
      if (len<1020) {
         command[len++]=c1;
         command[len]='\0';
      }
      if (c1=='\0') {
         break;
      }
   }
   command[1022]='\0';

   jp_logf(JP_LOG_STDOUT|JP_LOG_FILE, _("executing command = [%s]\n"), command);
   system(command);
}

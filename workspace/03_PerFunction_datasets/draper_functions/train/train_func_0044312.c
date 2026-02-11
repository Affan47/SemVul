set_begin_end_labels(struct tm *begin, struct tm *end, int flags)
{
   char str[255];
   char time1_str[255];
   char time2_str[255];
   char pref_time[40];
   const char *pref_date;

   str[0]='\0';

   get_pref(PREF_SHORTDATE, NULL, &pref_date);
   strftime(str, sizeof(str), pref_date, begin);
   gtk_label_set_text(GTK_LABEL(GTK_BIN(begin_date_button)->child), str);

   if (flags & UPDATE_DATE_ENTRIES) {
      if (GTK_TOGGLE_BUTTON(radio_button_no_time)->active) {
         gtk_entry_set_text(GTK_ENTRY(begin_time_entry), "");
         gtk_entry_set_text(GTK_ENTRY(end_time_entry), "");
      } else {
         get_pref_time_no_secs(pref_time);

         jp_strftime(time1_str, sizeof(time1_str), pref_time, begin);
         jp_strftime(time2_str, sizeof(time2_str), pref_time, end);

         gtk_entry_set_text(GTK_ENTRY(begin_time_entry), time1_str);
         gtk_entry_set_text(GTK_ENTRY(end_time_entry), time2_str);
      }
   }
   if (flags & UPDATE_DATE_MENUS) {
      gtk_option_menu_set_history(GTK_OPTION_MENU(option1), begin_date.tm_hour);
      gtk_option_menu_set_history(GTK_OPTION_MENU(option2), begin_date.tm_min/5);
      gtk_option_menu_set_history(GTK_OPTION_MENU(option3), end_date.tm_hour);
      gtk_option_menu_set_history(GTK_OPTION_MENU(option4), end_date.tm_min/5);
   }
}

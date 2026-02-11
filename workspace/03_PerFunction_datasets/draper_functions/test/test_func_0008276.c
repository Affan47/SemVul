appt_clear_details(void)
{
   int i;
   struct tm today;
   int new_cat;
   int sorted_position;
#ifdef ENABLE_DATEBK
   long use_db3_tags;
#endif

   connect_changed_signals(DISCONNECT_SIGNALS);

   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_alarm), FALSE);
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_button_no_time), TRUE);
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(private_checkbox), FALSE);

   clear_begin_end_labels();

   gtk_text_buffer_set_text(GTK_TEXT_BUFFER(dbook_desc_buffer), "", -1);
   gtk_text_buffer_set_text(GTK_TEXT_BUFFER(dbook_note_buffer), "", -1);
#ifdef ENABLE_DATEBK
   get_pref(PREF_USE_DB3, &use_db3_tags, NULL);
   if (use_db3_tags) {
      gtk_entry_set_text(GTK_ENTRY(datebk_entry), "");
   }
#endif
   if (datebook_version) {

      gtk_entry_set_text(GTK_ENTRY(location_entry), "");
   }


   gtk_notebook_set_page(GTK_NOTEBOOK(notebook), PAGE_NONE);

   gtk_entry_set_text(GTK_ENTRY(units_entry), "5");
   gtk_entry_set_text(GTK_ENTRY(repeat_day_entry), "1");
   gtk_entry_set_text(GTK_ENTRY(repeat_week_entry), "1");
   gtk_entry_set_text(GTK_ENTRY(repeat_mon_entry), "1");
   gtk_entry_set_text(GTK_ENTRY(repeat_year_entry), "1");

   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_day_endon), FALSE);
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_week_endon), FALSE);
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_mon_endon), FALSE);
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button_year_endon), FALSE);

   for(i=0; i<7; i++) {
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(toggle_button_repeat_days[i]), FALSE);
   }

   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(toggle_button_repeat_mon_bydate), TRUE);

   memset(&today, 0, sizeof(today));
   today.tm_year = current_year;
   today.tm_mon = current_month;
   today.tm_mday = current_day;
   today.tm_hour = 12;
   today.tm_min = 0;
   mktime(&today);
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(toggle_button_repeat_days[today.tm_wday]), TRUE);

   memcpy(&glob_endon_day_tm, &today, sizeof(glob_endon_day_tm));
   memcpy(&glob_endon_week_tm, &today, sizeof(glob_endon_week_tm));
   memcpy(&glob_endon_mon_tm, &today, sizeof(glob_endon_mon_tm));
   memcpy(&glob_endon_year_tm, &today, sizeof(glob_endon_year_tm));

   if (datebook_version) {

      if (dbook_category==CATEGORY_ALL) {
         new_cat = 0;
      } else {
         new_cat = dbook_category;
      }
      sorted_position = find_sort_cat_pos(new_cat);
      if (sorted_position<0) {
         jp_logf(JP_LOG_WARN, _("Category is not legal\n"));
      } else {
         gtk_check_menu_item_set_active
           (GTK_CHECK_MENU_ITEM(dbook_cat_menu_item2[sorted_position]), TRUE);
         gtk_option_menu_set_history(GTK_OPTION_MENU(category_menu2),
                                     find_menu_cat_pos(sorted_position));
      }
   }

   connect_changed_signals(CONNECT_SIGNALS);
}

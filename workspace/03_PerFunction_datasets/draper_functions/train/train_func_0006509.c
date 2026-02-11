todo_clear_details(void)
{
   time_t ltime;
   struct tm *now;
   int new_cat;
   int sorted_position;
   long default_due, till_due;

   time(&ltime);
   now = localtime(&ltime);


   connect_changed_signals(DISCONNECT_SIGNALS);

   gtk_widget_freeze_child_notify(todo_desc);
   gtk_widget_freeze_child_notify(todo_note);

   gtk_text_buffer_set_text(GTK_TEXT_BUFFER(todo_desc_buffer), "", -1);
   gtk_text_buffer_set_text(GTK_TEXT_BUFFER(todo_note_buffer), "", -1);

   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_button_todo[0]), TRUE);

   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(todo_completed_checkbox), FALSE);

   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(private_checkbox), FALSE);

   get_pref(PREF_TODO_DAYS_DUE, &default_due, NULL);
   get_pref(PREF_TODO_DAYS_TILL_DUE, &till_due, NULL);
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(todo_no_due_date_checkbox),
                                ! default_due);

   memcpy(&due_date, now, sizeof(struct tm));

   if (default_due) {
      add_days_to_date(&due_date, till_due);
      update_due_button(due_date_button, &due_date);
   } else {
      update_due_button(due_date_button, NULL);
   }

   gtk_widget_thaw_child_notify(todo_desc);
   gtk_widget_thaw_child_notify(todo_note);

   if (todo_category==CATEGORY_ALL) {
      new_cat = 0;
   } else {
      new_cat = todo_category;
   }
   sorted_position = find_sort_cat_pos(new_cat);
   if (sorted_position<0) {
      jp_logf(JP_LOG_WARN, _("Category is not legal\n"));
   } else {
      gtk_check_menu_item_set_active
        (GTK_CHECK_MENU_ITEM(todo_cat_menu_item2[sorted_position]), TRUE);
      gtk_option_menu_set_history(GTK_OPTION_MENU(category_menu2),
                                  find_menu_cat_pos(sorted_position));
   }

   set_new_button_to(CLEAR_FLAG);
   connect_changed_signals(CONNECT_SIGNALS);

   return EXIT_SUCCESS;
}

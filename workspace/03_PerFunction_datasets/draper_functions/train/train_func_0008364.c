stop_callback ( GtkAction *act )
{
  TaskData *td;
  time_t now, diff;
  int st = get_selected_task ();

  if ( st < 0 || ! num_visible_tasks ) {
    create_confirm_window ( CONFIRM_ERROR,
      gettext("Error"),
      gettext("You have not selected\na task to stop timing."),
      gettext("Ok"), NULL, NULL,
      NULL, NULL, NULL,
      NULL );
  } else {
    td = visible_tasks[st];
    if ( ! td->timer_on ) {
      create_confirm_window ( CONFIRM_ERROR,
        gettext("Error"),
        gettext("Task is not being timed."),
        gettext("Ok"), NULL, NULL,
        NULL, NULL, NULL,
        NULL );
    } else {
      td->timer_on = 0;
      time ( &now );
      diff = now - td->on_since;
      td->todays_entry->seconds += diff;
      td->on_since = 0;
      update_list ();
      num_timing--;
      if ( num_timing == 0 )
        gdk_window_set_icon ( GTK_WIDGET ( main_window )->window,
          NULL, appicon2, appicon2_mask );
    }
  }
  update_toolbar_buttons ();
}

adjust_task_time ( offset )
int offset;
{
  TaskData *td;
  int st = get_selected_task ();

  if ( st < 0 ) {
    create_confirm_window ( CONFIRM_ERROR,
      gettext("Error"),
      gettext("You have not selected\na task to adjust the time for."),
      gettext("Ok"), NULL, NULL,
      NULL, NULL, NULL,
      NULL );
  } else {
    update_tasks ();
    td = visible_tasks[st];
    if ( td->todays_entry == NULL )
      td->todays_entry = taskNewTimeEntry ( td->task,
        today_year, today_mon, today_mday );
    if ( offset == 0 ) {

      cutBuffer = td->todays_entry->seconds;
      td->todays_entry->seconds = 0;
    } else if ( offset < 0 ) {

      if ( td->todays_entry->seconds < ( 0 - offset ) ) {
        cutBuffer += td->todays_entry->seconds;
        td->todays_entry->seconds = 0;
      } else {
        cutBuffer += - offset;
        td->todays_entry->seconds += offset;
      }
    } else {
      td->todays_entry->seconds += offset;
    }
    modified_since_save = 1;
    update_list ();
  }
}

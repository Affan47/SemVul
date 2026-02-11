wnck_task_button_toggled (GtkButton *button,
			  WnckTask  *task)
{

  if (task->really_toggling)
    return;


  task->really_toggling = TRUE;
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button),
				!gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (button)));
  task->really_toggling = FALSE;

  switch (task->type)
    {
    case WNCK_TASK_CLASS_GROUP:
      wnck_task_popup_menu (task, FALSE);
      break;
    case WNCK_TASK_WINDOW:
      if (task->window == NULL)
	return;


      wnck_tasklist_activate_task_window (task, gtk_get_current_event_time ());
      break;
    case WNCK_TASK_STARTUP_SEQUENCE:
      break;
    }
}

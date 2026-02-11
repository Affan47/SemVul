task_selected_callback ( widget, col, row, bevent, user_data )
GtkWidget *widget;
int col;
int row;
GdkEventButton *bevent;
gpointer user_data;
{
  int i;

  if ( rebuilding_list )
    return ( TRUE );

  for ( i = 0; i < num_visible_tasks; i++ )
    visible_tasks[i]->selected = 0;

  selected_task = col;
  if ( selected_task >= 0 )
    visible_tasks[selected_task]->selected = 1;

  if ( bevent != NULL ) {

    if ( bevent->type == GDK_2BUTTON_PRESS )
      switch_to_callback ( widget, user_data );
  }

  return ( TRUE );
}

add_event( gpointer data, gpointer user_data GCC_UNUSED )
{
  event_t *ptr = data;
  GtkTreeIter it;

  if( ptr->type != event_type_null ) {
    gtk_list_store_append( events_model, &it );
    gtk_list_store_set( events_model, &it, EVENTS_COLUMN_TIME, ptr->tstates, EVENTS_COLUMN_TYPE, event_name( ptr->type ), -1 );
  }
}

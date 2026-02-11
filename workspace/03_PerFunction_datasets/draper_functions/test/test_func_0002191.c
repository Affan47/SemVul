eprop_treeview_key_press (GtkWidget * treeview,
                          GdkEventKey * event, GladeEditorProperty * eprop)
{
  if (event->keyval == GDK_KEY_Delete)
    {
      glade_eprop_model_data_delete_selected (eprop);
      return TRUE;
    }
  else if ((event->state & GDK_CONTROL_MASK) != 0 &&
           (event->keyval == GDK_KEY_n || event->keyval == GDK_KEY_N))
    {
      glade_eprop_model_data_add_row (eprop);
      return TRUE;
    }

  return FALSE;
}

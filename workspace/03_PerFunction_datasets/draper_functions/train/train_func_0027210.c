live_search_entry_key_pressed_cb (GtkEntry *entry,
    GdkEventKey *event,
    gpointer user_data)
{
  TpawLiveSearch *self = TPAW_LIVE_SEARCH (user_data);


  if (event->keyval == GDK_KEY_Escape)
    {
      gtk_widget_hide (GTK_WIDGET (self));
      return TRUE;
    }


  if (event->keyval == GDK_KEY_Up || event->keyval == GDK_KEY_Down
      || event->keyval == GDK_KEY_Page_Up || event->keyval == GDK_KEY_Page_Down
      || event->keyval == GDK_KEY_Menu)
     {
       return fire_key_navigation_sig (self, event);
     }

  if (event->keyval == GDK_KEY_Home || event->keyval == GDK_KEY_End ||
      event->keyval == GDK_KEY_space)
    {


      if (!gtk_widget_get_visible (GTK_WIDGET (self)))
        {
          return fire_key_navigation_sig (self, event);
        }
    }

  return FALSE;
}

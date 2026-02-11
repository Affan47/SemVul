activate_cb (GtkWidget *menuitem, gpointer data)
{
  MenuData *md;

  g_return_if_fail (GTK_IS_WIDGET (menuitem));

  md = data;

  meta_frames_notify_menu_hide (md->menu->frames);
  (* md->menu->func) (md->menu,
                      GDK_DISPLAY_XDISPLAY (gdk_display_get_default ()),
                      md->menu->client_xwindow,
                      gtk_get_current_event_time (),
                      md->op,
                      GPOINTER_TO_INT (g_object_get_data (G_OBJECT (menuitem),
                                                          "workspace")),
                      md->menu->data);


}

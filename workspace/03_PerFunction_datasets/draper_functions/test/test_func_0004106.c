panelapplet_reorient_cb (GtkWidget *applet, PanelAppletOrient neworient,
    gpointer data)
{
  GtkWidget *menubar = (GtkWidget *)data;
  if ((((neworient == PANEL_APPLET_ORIENT_UP) ||
      (neworient == PANEL_APPLET_ORIENT_DOWN)) &&
      ((orient == PANEL_APPLET_ORIENT_LEFT) ||
      (orient == PANEL_APPLET_ORIENT_RIGHT))) ||
      (((neworient == PANEL_APPLET_ORIENT_LEFT) ||
      (neworient == PANEL_APPLET_ORIENT_RIGHT)) &&
      ((orient == PANEL_APPLET_ORIENT_UP) ||
      (orient == PANEL_APPLET_ORIENT_DOWN)))) {
    packdirection = (packdirection == GTK_PACK_DIRECTION_LTR) ?
        GTK_PACK_DIRECTION_TTB : GTK_PACK_DIRECTION_LTR;
    gtk_menu_bar_set_pack_direction(GTK_MENU_BAR(menubar),
        packdirection);
    orient = neworient;
    gtk_container_foreach(GTK_CONTAINER(menubar),
        (GtkCallback)reorient_box_cb, NULL);
  }
  orient = neworient;
  return FALSE;
}

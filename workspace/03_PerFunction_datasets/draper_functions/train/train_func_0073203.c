classbrowser_show_hide(GtkWidget *widget)
{
  gboolean hidden;
  g_object_get(main_window.prefmg, "side_panel_hidden", &hidden, NULL);
  menubar_set_classbrowser_status(MENUBAR(main_window.menu), hidden);
  if (hidden)
    classbrowser_show();
  else
    classbrowser_hide();
}

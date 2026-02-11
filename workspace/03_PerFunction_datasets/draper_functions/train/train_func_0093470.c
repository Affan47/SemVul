remember_fe_cb (gpointer data, guint action, GtkWidget *w )
{
  if (GTK_CHECK_MENU_ITEM(w)->active)
    write_config ("remember_frontend", "yes");
  else
    write_config ("remember_frontend", "no");
}

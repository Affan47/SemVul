on_menu_tenses_activate (GtkWidget *widget,
                         gpointer   data)
{
  if (!window_tenses)
    window_tenses = create_window_tenses ();
  gtk_window_present ((GtkWindow *) window_tenses);
}

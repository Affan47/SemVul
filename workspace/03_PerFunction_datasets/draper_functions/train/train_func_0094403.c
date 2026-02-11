apwalapp_goto_iconsel(apwalapp_t *apwal)
{
  g_assert(apwal != NULL);
  if (apwal->apwal_pref->iconsel_in_a_separate_window == TRUE)
  {
    if (apwal->apwal_pref->iconsel_modal)
    {
      gtk_grab_add(apwal->window2);
    }
    gtk_widget_show(apwal->window2);
    gtk_notebook_set_current_page(GTK_NOTEBOOK(apwal->notebook2), 0);
  }
  else
    gtk_notebook_set_current_page(GTK_NOTEBOOK(apwal->notebook), 1);
}

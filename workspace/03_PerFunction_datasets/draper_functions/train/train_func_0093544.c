x_compselect_open (GSCHEM_TOPLEVEL *w_current)
{
  GtkWidget *current_tab, *entry_filter;
  GtkNotebook *compselect_notebook;

  if (w_current->cswindow == NULL) {
    w_current->cswindow = GTK_WIDGET (
      g_object_new (TYPE_COMPSELECT,

                    "settings-name", "compselect",
                    "gschem-toplevel", w_current,
                    NULL));

    g_signal_connect (w_current->cswindow,
                      "response",
                      G_CALLBACK (x_compselect_callback_response),
                      w_current);

    gtk_window_set_transient_for (GTK_WINDOW (w_current->cswindow),
                                  GTK_WINDOW (w_current->main_window));

    gtk_widget_show (w_current->cswindow);

  } else {
    gtk_window_present (GTK_WINDOW (w_current->cswindow));
  }
  gtk_editable_select_region (GTK_EDITABLE (COMPSELECT (w_current->cswindow)->entry_filter), 0, -1);


  compselect_notebook = GTK_NOTEBOOK (COMPSELECT (w_current->cswindow)->viewtabs);
  current_tab = gtk_notebook_get_nth_page (compselect_notebook,
                                           gtk_notebook_get_current_page (compselect_notebook));
  entry_filter = GTK_WIDGET (COMPSELECT (w_current->cswindow)->entry_filter);
  if (gtk_widget_is_ancestor (entry_filter, current_tab)) {
    gtk_widget_grab_focus (entry_filter);
  }
}

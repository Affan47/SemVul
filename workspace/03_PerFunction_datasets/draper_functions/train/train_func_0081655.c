x_multiattrib_open (GSCHEM_TOPLEVEL *w_current)
{
  if ( w_current->mawindow == NULL ) {
    w_current->mawindow =
      GTK_WIDGET (g_object_new (TYPE_MULTIATTRIB,
                                "object", NULL,

                                "settings-name", "multiattrib",
                                "gschem-toplevel", w_current,
                                NULL));

    gtk_window_set_transient_for (GTK_WINDOW(w_current->mawindow),
                                  GTK_WINDOW(w_current->main_window));

    g_signal_connect (w_current->mawindow,
                      "response",
                      G_CALLBACK (multiattrib_callback_response),
                      w_current);


    x_multiattrib_update (w_current);

    gtk_widget_show (w_current->mawindow);
  } else {
    gtk_window_present (GTK_WINDOW(w_current->mawindow));
  }
}

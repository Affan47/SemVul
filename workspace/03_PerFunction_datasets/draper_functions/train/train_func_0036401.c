display_add (displayd * display, ggobid * gg)
{
  splotd *prev_splot = gg->current_splot;
  ProjectionMode pmode_prev = pmode_get (gg->current_display, gg);
  InteractionMode imode_prev = imode_get (gg);


  if (g_list_find (gg->displays, display)) {
    g_printerr
      ("Display has already been added to the displays list of this ggobi\n");
    return (-1);
  }


  if (g_list_length (display->splots)) {
    gg->current_splot = (splotd *)
      g_list_nth_data (display->splots, 0);
    display->current_splot = gg->current_splot;
    splot_set_current (gg->current_splot, on, gg);
  }

  if (GGOBI_IS_WINDOW_DISPLAY (display)
      && GGOBI_WINDOW_DISPLAY (display)->useWindow) {
    GGobi_widget_set (GGOBI_WINDOW_DISPLAY (display)->window, gg, true);
  }

  g_signal_connect(G_OBJECT(display), "destroy",
      G_CALLBACK(display_destroy_cb), gg);

  if (g_list_length (display->splots))
      display_set_current (display, gg);

  gg->displays = g_list_append (gg->displays, (gpointer) display);


  display_add_tree (display);


  if (pmode_prev != gg->current_display->cpanel.pmode ||
      imode_prev != gg->current_display->cpanel.imode) {

    display_mode_menus_update (pmode_prev, imode_prev,
                               gg->current_display, gg);
  }


  if (prev_splot != NULL) {
    prev_splot->redraw_style = QUICK;
    gtk_widget_queue_draw (prev_splot->da);
  }

  g_signal_emit (G_OBJECT (gg), GGobiSignals[DISPLAY_NEW_SIGNAL], 0, display);

  return (g_list_length (gg->displays));
}

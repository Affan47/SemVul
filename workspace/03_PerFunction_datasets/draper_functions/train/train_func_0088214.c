symbol_window_redraw (ggobid * gg)
{


  gint k;
  splotd *sp = gg->current_splot;
  gint rval = false;

  if (gg->color_ui.symbol_display) {

    g_signal_emit_by_name (G_OBJECT (gg->color_ui.symbol_display),
                           "expose_event", (gpointer) sp, (gpointer) & rval);
    g_signal_emit_by_name (G_OBJECT (gg->color_ui.line_display),
                           "expose_event", (gpointer) sp, (gpointer) & rval);
    redraw_bg (gg->color_ui.bg_da, gg);
    redraw_accent (gg->color_ui.accent_da, gg);

    for (k = 0; k < gg->activeColorScheme->n; k++) {
      gtk_widget_show (gg->color_ui.fg_da[k]);
      redraw_fg (gg->color_ui.fg_da[k], k, gg);
    }
    for (k = gg->activeColorScheme->n; k < MAXNCOLORS; k++) {
      gtk_widget_hide (gg->color_ui.fg_da[k]);
    }
  }
}

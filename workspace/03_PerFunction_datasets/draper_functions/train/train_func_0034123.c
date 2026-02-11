cpanelSet (displayd * dpy, cpaneld * cpanel, ggobid * gg)
{
  GtkWidget *w;
  w = GGOBI_EXTENDED_DISPLAY (dpy)->cpanelWidget;
  if (!w) {
    GGOBI_EXTENDED_DISPLAY (dpy)->cpanelWidget = w =
      cpanel_parcoords_make (gg);
  }

  cpanel_parcoords_set (dpy, cpanel, w, gg);
  cpanel_brush_set (dpy, cpanel, gg);
  cpanel_identify_set (dpy, cpanel, gg);

  return (true);
}

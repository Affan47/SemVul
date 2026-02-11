motion_notify_cb (GtkWidget * w, GdkEventMotion * event, splotd * sp)
{
  gboolean button1_p, button2_p;
  ggobid *gg = GGobiFromSPlot (sp);
  displayd *display = (displayd *) sp->displayptr;
  cpaneld *cpanel = &display->cpanel;


  mousepos_get_motion (w, event, &button1_p, &button2_p, sp);


  if (!button1_p && !button2_p)
    return false;


  if (sp->mousepos.x == sp->mousepos_o.x
      && sp->mousepos.y == sp->mousepos_o.y)
    return false;

  if (button1_p) {
    pan_by_drag (sp, gg);
  }
  else if (button2_p) {
    zoom_by_drag (sp, gg);
  }

  if (cpanel->scale.updateAlways_p) {

    splot_plane_to_screen (display, &display->cpanel, sp, gg);
    ruler_ranges_set (false, gg->current_display, sp, gg);
    splot_redraw (sp, FULL, gg);
  }
  else {
    splot_redraw (sp, QUICK, gg);
  }

  sp->mousepos_o.x = sp->mousepos.x;
  sp->mousepos_o.y = sp->mousepos.y;

  return true;
}

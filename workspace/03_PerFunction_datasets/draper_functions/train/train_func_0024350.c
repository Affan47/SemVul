zoom_cb (GtkAdjustment * adj, ggobid * gg)
{
  displayd *display = gg->current_display;
  splotd *sp = gg->current_splot;
  cpaneld *cpanel = &display->cpanel;
  gchar *name = (gchar *) g_object_get_data (G_OBJECT (adj), "name");
  greal oscalex = sp->scale.x, oscaley = sp->scale.y;
  GtkAdjustment *adj_other;


  gdouble expvalue = pow (10., adj->value), step = 0.0;
  gdouble eps = .0001, exp_eps = .001;


  if (display != sp->displayptr)
    return;

  if (strcmp (name, "SCALE:x_zoom_adj") == 0) {
    cpanel->scale.zoomval.x = adj->value;
    step = adj->value - log10 (sp->scale.x);
    sp->scale.x = expvalue;
    if (cpanel->scale.fixAspect_p && fabs (step) > eps) {
      adj_other = scale_adjustment_find_by_name ("SCALE:y_zoom", gg);
      sp->scale.y = pow (10., adj_other->value + step);
      increment_adjustment (adj_other, step, eps);
    }
  }
  else {
    cpanel->scale.zoomval.y = adj->value;
    step = adj->value - log10 (sp->scale.y);
    sp->scale.y = expvalue;
    if (cpanel->scale.fixAspect_p && fabs (step) > eps) {
      adj_other = scale_adjustment_find_by_name ("SCALE:x_zoom", gg);
      sp->scale.x = pow (10.0, adj_other->value + step);
      increment_adjustment (adj_other, step, eps);
    }
  }

  if (fabs (oscalex - sp->scale.x) > exp_eps ||
      fabs (oscaley - sp->scale.y) > exp_eps) {
    splot_plane_to_screen (display, cpanel, sp, gg);
    ruler_ranges_set (false, display, sp, gg);
    splot_redraw (sp, FULL, gg);
  }
}

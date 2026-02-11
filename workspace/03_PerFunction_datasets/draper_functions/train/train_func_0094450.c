tour2d_varsel (GtkWidget *w, gint jvar, gint toggle, gint mouse,
  GGobiData *d, ggobid *gg)
{
  displayd *dsp = gg->current_display;
  gboolean changed = true;

  if (GTK_IS_TOGGLE_BUTTON(w) || GTK_IS_BUTTON(w)) {


    gboolean fade = gg->tour2d.fade_vars;

    changed = tour2d_subset_var_set(jvar, d, dsp, gg);
    if (changed) {
      varcircles_visibility_set (dsp, gg);


      gg->tour2d.fade_vars = false;
      tour2d_active_var_set (jvar, d, dsp, gg);
      gg->tour2d.fade_vars = fade;
    }

  } else if (GTK_IS_DRAWING_AREA(w)) {


    if (d->vcirc_ui.jcursor == GDK_HAND2) {
      tour2d_manip_var_set (jvar, gg);
      varcircles_cursor_set_default (d);

    } else {

      tour2d_active_var_set (jvar, d, dsp, gg);

    }
  }

  return changed;
}

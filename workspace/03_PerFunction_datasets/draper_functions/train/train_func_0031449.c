sphere_apply_cb (GtkWidget * w, ggobid * gg)
{


  gfloat firstpc, lastpc;
  GGobiData *d = datad_get_from_window (gg->sphere_ui.window);

  if (d == NULL)
    return;
  if (d->sphere.eigenval.els == NULL)
    return;

  firstpc = d->sphere.eigenval.els[0];
  lastpc = d->sphere.eigenval.els[d->sphere.npcs - 1];

  if (d->sphere.npcs > 0 && d->sphere.npcs <= d->sphere.vars.nels) {
    if (lastpc == 0.0 || firstpc / lastpc > 10000.0) {
      quick_message ("Need to choose fewer PCs. Var-cov close to singular.",
                     false);
    }
    else {

      if (spherize_set_pcvars (d, gg)) {


        spherize_data (&d->sphere.vars, &d->sphere.pcvars, d, gg);
        sphere_varcovar_set (d, gg);


        limits_set (d, false, true, gg->lims_use_visible);
        vartable_limits_set (d);
        vartable_stats_set (d);

        tform_to_world (d, gg);
        displays_tailpipe (FULL, gg);
      }
    }
  }
}

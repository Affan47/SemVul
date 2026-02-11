tour2d_reinit(ggobid *gg)
{
  gint i;
  displayd *dsp = gg->current_display;
  GGobiData *d = dsp->d;
  splotd *sp = gg->current_splot;

  arrayd_zero (&dsp->t2d.Fa);
  arrayd_zero (&dsp->t2d.Fz);
  arrayd_zero (&dsp->t2d.F);
  arrayd_zero (&dsp->t2d.Ga);
  arrayd_zero (&dsp->t2d.Gz);

  for (i=0; i<2; i++)
  {
    dsp->t2d.Fz.vals[i][dsp->t2d.active_vars.els[i]] =
      dsp->t2d.Fa.vals[i][dsp->t2d.active_vars.els[i]] =
      dsp->t2d.F.vals[i][dsp->t2d.active_vars.els[i]] =
      dsp->t2d.Ga.vals[i][dsp->t2d.active_vars.els[i]] =
      dsp->t2d.Gz.vals[i][dsp->t2d.active_vars.els[i]] = 1.0;
  }


  dsp->t2d.tau.els[0] = 0.0;
  dsp->t2d.tau.els[1] = 0.0;

  dsp->t2d.get_new_target = true;

  sp->tour2d.initmax = true;

  display_tailpipe (dsp, FULL, gg);

  varcircles_refresh (d, gg);

  if (dsp->t2d_window != NULL && GTK_WIDGET_VISIBLE (dsp->t2d_window))
    t2d_pp_reinit(dsp, gg);
}

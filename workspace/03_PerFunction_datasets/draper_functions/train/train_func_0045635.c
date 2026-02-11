display_tour2d3_init (displayd *dsp, ggobid *gg) {
  gint i, j;
  GGobiData *d = dsp->d;
  cpaneld *cpanel = &dsp->cpanel;
  gint nc = d->ncols;

  if (nc < MIN_NVARS_FOR_TOUR2D3)
    return;

  alloc_tour2d3(dsp, gg);


  dsp->t2d3.nsubset = dsp->t2d3.nactive = 3;
  for (j=0; j<nc; j++) {
    dsp->t2d3.subset_vars.els[j] = dsp->t2d3.active_vars.els[j] = 0;
    dsp->t2d3.subset_vars_p.els[j] = dsp->t2d3.active_vars_p.els[j] = false;
  }
  for (j=0; j<3; j++) {
    dsp->t2d3.subset_vars.els[j] = dsp->t2d3.active_vars.els[j] = j;
    dsp->t2d3.subset_vars_p.els[j] = dsp->t2d3.active_vars_p.els[j] = true;
  }


  arrayd_zero (&dsp->t2d3.Fa);
  arrayd_zero (&dsp->t2d3.Fz);
  arrayd_zero (&dsp->t2d3.F);
  arrayd_zero (&dsp->t2d3.Ga);
  arrayd_zero (&dsp->t2d3.Gz);

  for (i=0; i<2; i++) {
    dsp->t2d3.Fz.vals[i][dsp->t2d3.active_vars.els[i]] =
      dsp->t2d3.Fa.vals[i][dsp->t2d3.active_vars.els[i]] =
      dsp->t2d3.F.vals[i][dsp->t2d3.active_vars.els[i]] =
      dsp->t2d3.Ga.vals[i][dsp->t2d3.active_vars.els[i]] =
      dsp->t2d3.Gz.vals[i][dsp->t2d3.active_vars.els[i]] = 1.0;
  }

  dsp->t2d3.dist_az = 0.0;
  dsp->t2d3.delta = cpanel->t2d3.step*M_PI_2/10.0;
  dsp->t2d3.tang = 0.0;

  dsp->t2d3.idled = 0;
  dsp->t2d3.get_new_target = true;


  dsp->t2d3_manip_var = 0;

  dsp->t2d.target_selection_method = 0;
}

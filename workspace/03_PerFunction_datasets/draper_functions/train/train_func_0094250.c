tour1d_manip_var_set (gint j, gint btn, ggobid *gg)
{
  displayd *dsp = gg->current_display;

  if (btn == 1)
    dsp->t1d_manip_var = j;
}

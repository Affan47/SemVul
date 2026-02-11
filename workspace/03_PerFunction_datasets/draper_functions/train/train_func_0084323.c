compute_a_curve_full(lut_t *lut, int channel)
{
  double *tmp;
  double pivot = .25;
  double ipivot = 1.0 - pivot;
  double xgamma = pow(pivot, lut->screen_gamma);
  double print_gamma=1.0+9.0*(lut->print_gamma-1.0);
  double pivot2 = .75;
  double ipivot2 = 1.0 - pivot2;
  double xgamma2 = pow(pivot2, print_gamma);
  stp_curve_t *curve = stp_curve_cache_get_curve(&(lut->channel_curves[channel]));
  int i;
  int isteps = lut->steps;
  if (isteps > 256)
    isteps = 256;
  tmp = stp_malloc(sizeof(double) * lut->steps);
  for (i = 0; i < isteps; i ++)
    {
      double pixel = (double) i / (double) (isteps - 1);

      if (lut->input_color_description->color_model == COLOR_BLACK)
	pixel = 1.0 - pixel;

      pixel = 1.0 -
	(1.0 / (1.0 - xgamma)) *
	(pow(pivot + ipivot * pixel, lut->screen_gamma) - xgamma);


      if (pixel < 0.0)
	pixel = 0.0;
      else if (pixel > 1.0)
	pixel = 1.0;

      if (pixel > .9999 && lut->gamma_values[channel] < .00001)
	pixel = 0;
      else
	pixel = 1 - pow(1 - pixel, lut->gamma_values[channel]);


      pixel = 65535 * (1.0 / (1.0 - xgamma2)) *
	(pow(pivot2 + ipivot2 * pixel, print_gamma) - xgamma2);
      if (lut->output_color_description->color_model == COLOR_WHITE)
	pixel = 65535 - pixel;

      if (pixel <= 0.0)
	tmp[i] = 0;
      else if (pixel >= 65535.0)
	tmp[i] = 65535;
      else
	tmp[i] = (pixel);
      tmp[i] = floor(tmp[i] + 0.5);
    }
  stp_curve_set_data(curve, isteps, tmp);
  if (isteps != lut->steps)
    stp_curve_resample(curve, lut->steps);
  stp_free(tmp);
}

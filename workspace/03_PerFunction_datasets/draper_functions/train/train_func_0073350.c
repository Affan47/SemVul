gst_audio_dynamic_transform_soft_knee_expander_int (GstAudioDynamic * filter,
    gint16 * data, guint num_samples)
{
  glong val;
  glong thr_p = filter->threshold * G_MAXINT16;
  glong thr_n = filter->threshold * G_MININT16;
  gdouble zero_p, zero_n;
  gdouble a_p, b_p, c_p;
  gdouble a_n, b_n, c_n;
  gdouble r2;


  if (filter->threshold == 0.0 || filter->ratio == 1.0)
    return;


  zero_p = (thr_p * (filter->ratio - 1.0)) / (1.0 + filter->ratio);
  zero_n = (thr_n * (filter->ratio - 1.0)) / (1.0 + filter->ratio);

  if (zero_p < 0.0)
    zero_p = 0.0;
  if (zero_n > 0.0)
    zero_n = 0.0;


  g_assert (thr_p != 0);
  g_assert (thr_n != 0);


  r2 = filter->ratio * filter->ratio;
  a_p = (1.0 - r2) / (4.0 * thr_p);
  b_p = (1.0 + r2) / 2.0;
  c_p = thr_p * (1.0 - b_p - a_p * thr_p);
  a_n = (1.0 - r2) / (4.0 * thr_n);
  b_n = (1.0 + r2) / 2.0;
  c_n = thr_n * (1.0 - b_n - a_n * thr_n);

  for (; num_samples; num_samples--) {
    val = *data;

    if (val < thr_p && val > zero_p) {
      val = a_p * val * val + b_p * val + c_p;
    } else if ((val <= zero_p && val > 0) || (val >= zero_n && val < 0)) {
      val = 0;
    } else if (val > thr_n && val < zero_n) {
      val = a_n * val * val + b_n * val + c_n;
    }
    *data++ = (gint16) CLAMP (val, G_MININT16, G_MAXINT16);
  }
}

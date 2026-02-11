slew_samples(struct timeval *raw,
             struct timeval *cooked,
             double dfreq,
             double doffset,
             int is_step_change,
             void *not_used)
{
  double delta_time;
  int i;
  for (i=0; i<n_samples; i++) {
    UTI_AdjustTimeval(&samples[i].when, cooked, &samples[i].when, &delta_time,
        dfreq, doffset);
    samples[i].offset += delta_time;
  }
}

filter_get_last_sample(struct MedianFilter *filter, struct timeval *sample_time, double *offset, double *dispersion)
{
  if (filter->last < 0)
    return 0;

  *sample_time = filter->samples[filter->last].sample_time;
  *offset = filter->samples[filter->last].offset;
  *dispersion = filter->samples[filter->last].dispersion;
  return 1;
}

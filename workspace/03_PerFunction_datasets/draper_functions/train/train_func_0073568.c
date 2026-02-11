get_parameter(int param) const
{
  switch (param) {
  case 1:
    return th_level * 100.0 / (parameter_t)SAMPLE_SPECS::max_amplitude;
  case 2:
    return th_time * 1000.0 / (parameter_t)samples_per_second();
  case 3:
    return atime * 1000.0 / (parameter_t)samples_per_second();
  case 4:
    return htime * 1000.0 / (parameter_t)samples_per_second();
  case 5:
    return rtime * 1000.0 / (parameter_t)samples_per_second();
  }
  DBC_NEVER_REACHED();
  return 0.0;
}

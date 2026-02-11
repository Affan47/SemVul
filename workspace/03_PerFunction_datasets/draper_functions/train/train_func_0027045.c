set_parameter(int param, parameter_t value) {
  switch (param) {
  case 1:
    th_level = SAMPLE_SPECS::max_amplitude * (value / 100.0);
    break;
  case 2:
    th_time = (value * (parameter_t)samples_per_second() / 1000.0);
    break;
  case 3:
    atime = (value * (parameter_t)samples_per_second() / 1000.0);
    break;
  case 4:
    htime = (value * (parameter_t)samples_per_second() / 1000.0);
    break;
  case 5:
    rtime = (value * (parameter_t)samples_per_second() / 1000.0);
    break;
  default:
    DBC_NEVER_REACHED();
  }
}

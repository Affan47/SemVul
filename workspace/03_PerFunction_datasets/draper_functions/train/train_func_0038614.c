set_parameter(int param, parameter_t value)
{
  switch (param) {
  case 1:
    gain = value / 100.0;
    break;
  case 2:
    maxnum_of_clipped = (int)value;
    break;
  default:
    DBC_NEVER_REACHED();
  }
}

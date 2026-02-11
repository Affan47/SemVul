set_parameter(int param, parameter_t value)
{
  switch (param) {
    case 1:
      gain = value / 100.0;
      break;

    case 2:
      channel_rep = static_cast<int>(value);
      channel_rep--;
      break;
  default:
    DBC_NEVER_REACHED();
  }
}

set_parameter(int param, CHAIN_OPERATOR::parameter_t value)
{
  switch (param) {
  case 1:
    openlevel_rep = value / 100.0;
    break;
  case 2:
    closelevel_rep = value / 100.0;
    break;
  case 3:
    rms_rep = (value != 0);
    break;
  case 4:
    reopen_count_param_rep = static_cast<int>(value);
    break;
  }
}

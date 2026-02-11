set_parameter(int param, CHAIN_OPERATOR::parameter_t value) {
  switch (param) {
  case 1:
    to_channel = static_cast<ch_type>(value);
    DBC_CHECK(to_channel > 0);
    to_channel--;
    break;
  }
}

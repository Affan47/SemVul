set_parameter(int param, CHAIN_OPERATOR::parameter_t value)
{
  EFFECT_MIXING::ch_type from_channel;

  switch (param) {
  case 1:
    from_channel = static_cast<EFFECT_MIXING::ch_type>(value);
    DBC_CHECK(from_channel > 0);
    EFFECT_AMPLIFY_CHANNEL::set_parameter(2, from_channel);
    break;
  }
}

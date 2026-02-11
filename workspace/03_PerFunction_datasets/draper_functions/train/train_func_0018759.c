set_parameter(int param, CHAIN_OPERATOR::parameter_t value)
{
  switch (param) {
  case 1:
    double lowlimit = 1.0f / EFFECT_PITCH_SHIFT::resample_low_limit * 100.0f;

    if (value <= lowlimit) {
      ECA_LOG_MSG(ECA_LOGGER::info,
		  "WARNING! Shift-% must be greater than " +
		  kvu_numtostr(lowlimit) +
		  "%! Limiting to the low-limit.");
      pmod_rep = lowlimit;
    }
    else {
      pmod_rep = value;
    }
    if (sbuf_repp != 0) {
      target_rate_rep = static_cast<long int>(samples_per_second() * 100.0 / pmod_rep);
    }
    else {
      target_rate_rep = 0;
    }
    break;
  }
}

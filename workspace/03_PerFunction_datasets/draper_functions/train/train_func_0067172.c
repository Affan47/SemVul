siren(uint32_t counter, uint32_t * mi, Melody * melody)
{
  siren_freq += siren_step;
  if (siren_freq > siren_stop) {
    siren_step *= -1;
    siren_freq = siren_stop;
  }
  if (siren_freq < siren_start) {
    siren_step *= -1;
    siren_freq = siren_start;
  }
  buzzerOn(siren_freq);
}

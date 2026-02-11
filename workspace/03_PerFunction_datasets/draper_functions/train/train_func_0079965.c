set_samples_per_second(SAMPLE_SPECS::sample_rate_t srate)
{
  if (srate > 0) {
    sample_rate_rep = srate;
    rate_set_rep = true;
  }
  else {
    rate_set_rep = false;
    sample_rate_rep = ECA_AUDIO_TIME::invalid_srate;
  }
}

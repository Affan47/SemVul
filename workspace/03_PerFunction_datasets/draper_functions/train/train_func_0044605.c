set_samples_per_second(SAMPLE_SPECS::sample_rate_t new_value)
{
  double ratio (new_value);
  ratio /= samples_per_second();
  set_position_in_samples(static_cast<SAMPLE_SPECS::sample_pos_t>(position_in_samples() * ratio));
  if (length_set() == true) {
    set_length_in_samples(static_cast<SAMPLE_SPECS::sample_pos_t>(length_in_samples() * ratio));
  }
  ECA_SAMPLERATE_AWARE::set_samples_per_second(new_value);
}

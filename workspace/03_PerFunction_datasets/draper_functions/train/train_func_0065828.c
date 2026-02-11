set_max_length_in_samples(SAMPLE_SPECS::sample_pos_t pos)
{
  max_length_in_samples_rep = pos;
  if (pos != -1 * samples_per_second()) {
    max_length_set_rep = true;
  }
  else {
    max_length_set_rep = false;
  }
}

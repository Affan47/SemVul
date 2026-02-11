check_tuning (Hash_table *table)
{
  const Hash_tuning *tuning = table->tuning;


  float epsilon = 0.1f;

  if (epsilon < tuning->growth_threshold
      && tuning->growth_threshold < 1 - epsilon
      && 1 + epsilon < tuning->growth_factor
      && 0 <= tuning->shrink_threshold
      && tuning->shrink_threshold + epsilon < tuning->shrink_factor
      && tuning->shrink_factor <= 1
      && tuning->shrink_threshold + epsilon < tuning->growth_threshold)
    return true;

  table->tuning = &default_tuning;
  return false;
}

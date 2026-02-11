Cardinality(void) const
{

  int count = 0;
  for (int i = 0; i < grid_size; i++) {
    if (grid_values[i] != R2_GRID_UNKNOWN_VALUE) {
      if (grid_values[i] != 0) count++;
    }
  }
  return count;
}

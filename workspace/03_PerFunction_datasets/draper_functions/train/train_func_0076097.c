mc_clear_properties(int *properties, int shift, int mask, int value)
{
  int k;
  for (k = 0; k < NUM_PROPERTIES; k++)
    if (((k >> shift) & mask) == value)
      properties[k] = 0;
}

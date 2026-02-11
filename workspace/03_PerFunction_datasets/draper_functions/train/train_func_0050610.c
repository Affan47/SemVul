does_surround(int move, int dr)
{
  if (DRAGON2(dr).surround_status)
    return 0;
  return compute_surroundings(dr, move, 0, NULL);
}

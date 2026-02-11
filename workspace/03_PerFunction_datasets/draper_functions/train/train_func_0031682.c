random_level(void)
{
  uint32 r;
  int level = 0;


  r = random_seed = random_seed * 69069 + 25173;


  while ((r & 0xC0000000U) == 0xC0000000U) { level++; r = r << 2; }
  Assert(level < NUM_LEVELS);
  return level;
}

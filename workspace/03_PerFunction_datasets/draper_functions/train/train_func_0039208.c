setSeeds(const long* seeds, int)
{
  setSeed(seeds ? *seeds : 19780503L, 0);
  theSeeds = seeds;
}

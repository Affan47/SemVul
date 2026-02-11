countOnes(uint32_t* mask, int32_t len) {
  int32_t i, totalOnes = 0;
  for (i = 0 ; i < len ; ++i) {
    uint32_t ent = mask[i];
    for (; ent; totalOnes++)
    {
      ent &= ent - 1;
    }
  }
  return totalOnes;
}

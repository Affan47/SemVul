SectorUsedAs(uint64_t sector, int topPartNum) {
   int i = 0, usedAs = NONE;

   do {
      if ((partitions[i].GetStartLBA() <= sector) && (partitions[i].GetLastLBA() >= sector))
         usedAs = partitions[i].GetInclusion();
      if ((partitions[i].GetStartLBA() == (sector + 1)) && (partitions[i].GetInclusion() == LOGICAL))
         usedAs = EBR;
      if (sector == 0)
         usedAs = EBR;
      if (sector >= diskSize)
         usedAs = INVALID;
      i++;
   } while ((i < topPartNum) && ((usedAs == NONE) || (usedAs == EBR)));
   return usedAs;
}

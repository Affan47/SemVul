TrimPrimaries(void) {
   int numToDelete, i = MAX_MBR_PARTS;

   numToDelete = NumPrimaries() - 4;
   while ((numToDelete > 0) && (i >= 0)) {
      if (partitions[i].GetInclusion() == PRIMARY) {
         partitions[i].SetInclusion(NONE);
         numToDelete--;
      }
      i--;
   }
}

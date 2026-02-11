CountParts(void) {
   uint32_t i, counted = 0;

   for (i = 0; i < numParts; i++) {
      if (partitions[i].IsUsed())
         counted++;
   }
   return counted;
}

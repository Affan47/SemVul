SetPartitionGUID(uint32_t pn, GUIDData theGUID) {
   int retval = 0;

   if (pn < numParts) {
      if (partitions[pn].IsUsed()) {
         partitions[pn].SetUniqueGUID(theGUID);
         retval = 1;
      }
   }
   return retval;
}

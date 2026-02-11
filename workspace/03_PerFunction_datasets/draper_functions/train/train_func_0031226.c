SetPartType(int num, int type) {
   int allOK = 1;

   if ((num >= 0) && (num < MAX_MBR_PARTS)) {
      if (partitions[num].GetLengthLBA() != UINT32_C(0)) {
         allOK = partitions[num].SetType(type);
      } else allOK = 0;
   } else allOK = 0;
   return allOK;
}

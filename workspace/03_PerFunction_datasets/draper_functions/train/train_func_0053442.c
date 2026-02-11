SetPartBootable(int num, int bootable) {
   int allOK = 1;

   if ((num >= 0) && (num < MAX_MBR_PARTS)) {
      if (partitions[num].GetLengthLBA() != UINT32_C(0)) {
         if (bootable == 0)
            partitions[num].SetStatus(UINT8_C(0x00));
         else
            partitions[num].SetStatus(UINT8_C(0x80));
      } else allOK = 0;
   } else allOK = 0;
   return allOK;
}

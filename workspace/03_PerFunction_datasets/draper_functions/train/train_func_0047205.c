CreateExtended(void) {
   int allOK = 1, i = 0, swapped = 0;
   MBRPart temp;

   if (IsLegal()) {

      RemoveLogicalsFromFirstFour();

      MovePrimariesToFirstFour();


      if (NumLogicals() > 0) {
         SortMBR(4);
         temp.Empty();
         temp.SetStartLBA(FirstLogicalLBA() - 1);
         temp.SetLengthLBA(LastLogicalLBA() - FirstLogicalLBA() + 2);
         temp.SetType(0x0f, 1);
         temp.SetInclusion(PRIMARY);
         do {
            if ((partitions[i].GetInclusion() == NONE) || (partitions[i].GetLengthLBA() == 0)) {
               partitions[i] = temp;
               swapped = 1;
            }
            i++;
         } while ((i < 4) && !swapped);
         if (!swapped) {
            cerr << "Could not create extended partition; no room in primary table!\n";
            allOK = 0;
         }
      }
   } else allOK = 0;


   for (i = 0; i < MAX_MBR_PARTS; i++)
      if (swapped && partitions[i].GetType() == 0xEE)
         allOK = 0;
   return allOK;
}

UseWhichPartitions(void) {
   WhichToUse which = use_new;
   MBRValidity mbrState;

   mbrState = protectiveMBR.GetValidity();

   if ((state == gpt_invalid) && ((mbrState == mbr) || (mbrState == hybrid))) {
      cout << "\n***************************************************************\n"
           << "Found invalid GPT and valid MBR; converting MBR to GPT format\n"
           << "in memory. ";
      if (!justLooking) {
         cout << "\aTHIS OPERATION IS POTENTIALLY DESTRUCTIVE! Exit by\n"
              << "typing 'q' if you don't want to convert your MBR partitions\n"
              << "to GPT format!";
      }
      cout << "\n***************************************************************\n\n";
      which = use_mbr;
   }

   if ((state == gpt_invalid) && bsdFound) {
      cout << "\n**********************************************************************\n"
           << "Found invalid GPT and valid BSD disklabel; converting BSD disklabel\n"
           << "to GPT format.";
      if ((!justLooking) && (!beQuiet)) {
      cout << "\a THIS OPERATION IS POTENTIALLY DESTRUCTIVE! Your first\n"
           << "BSD partition will likely be unusable. Exit by typing 'q' if you don't\n"
           << "want to convert your BSD partitions to GPT format!";
      }
      cout << "\n**********************************************************************\n\n";
      which = use_bsd;
   }

   if ((state == gpt_valid) && (mbrState == gpt)) {
      which = use_gpt;
      if (!beQuiet)
         cout << "Found valid GPT with protective MBR; using GPT.\n";
   }
   if ((state == gpt_valid) && (mbrState == hybrid)) {
      which = use_gpt;
      if (!beQuiet)
         cout << "Found valid GPT with hybrid MBR; using GPT.\n";
   }
   if ((state == gpt_valid) && (mbrState == invalid)) {
      cout << "\aFound valid GPT with corrupt MBR; using GPT and will write new\n"
           << "protective MBR on save.\n";
      which = use_gpt;
   }
   if ((state == gpt_valid) && (mbrState == mbr)) {
      which = use_abort;
   }

   if (state == gpt_corrupt) {
      if (mbrState == gpt) {
         cout << "\a\a****************************************************************************\n"
              << "Caution: Found protective or hybrid MBR and corrupt GPT. Using GPT, but disk\n"
              << "verification and recovery are STRONGLY recommended.\n"
              << "****************************************************************************\n";
         which = use_gpt;
      } else {
         which = use_abort;
      }
   }

   if (which == use_new)
      cout << "Creating new GPT entries.\n";

   return which;
}

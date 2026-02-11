GetPartNum(void) {
   uint32_t partNum;
   uint32_t low, high;
   ostringstream prompt;

   if (GetPartRange(&low, &high) > 0) {
      prompt << "Partition number (" << low + 1 << "-" << high + 1 << "): ";
      partNum = GetNumber(low + 1, high + 1, low, prompt.str());
   } else partNum = 1;
   return (partNum - 1);
}

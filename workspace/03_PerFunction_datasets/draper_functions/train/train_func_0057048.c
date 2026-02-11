ArgusPrintTransactions (char *buf, struct ArgusRecord *ptr)
{
   struct ArgusAGRStruct *ArgusThisAgr = NULL;
   int hits = 1;

   if (ptr->ahdr.type & ARGUS_MAR) {
      sprintf(&buf[strlen(buf)], "      ");

   } else {
      ArgusThisAgr = (struct ArgusAGRStruct *)ArgusThisFarHdrs[ARGUS_AGR_DSR_INDEX];

      if (ArgusThisAgr && (ArgusThisAgr->type == ARGUS_AGR_DSR))
         hits = ArgusThisAgr->count;

      sprintf(&buf[strlen(buf)], "%5d ", hits);
   }
}

prt_cond(cond)
struct code *cond;
   {
   if (cond == &resume)
      fprintf(codefile, "A_Resume");
   else if (cond == &contin)
      fprintf(codefile, "A_Continue");
   else if (cond == &fallthru)
      fprintf(codefile, "A_FallThru");
   else {
      cond = ChkBound(cond);
      ChkSeqNum(cond);
      fprintf(codefile, "%d /* %s */", cond->SeqNum, cond->Desc);
      }
   }

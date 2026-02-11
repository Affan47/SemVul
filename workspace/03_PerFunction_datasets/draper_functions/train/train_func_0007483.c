ret_flag(db, flag, may_fthru)
FILE *db;
int flag;
int may_fthru;
   {
   if (flag & DoesFail)
      fprintf(db, "f");
   else
      fprintf(db, "_");
   if (flag & DoesRet)
      fprintf(db, "r");
   else
      fprintf(db, "_");
   if (flag & DoesSusp)
      fprintf(db, "s");
   else
      fprintf(db, "_");
   if (flag & DoesEFail)
      fprintf(db, "e");
   else
      fprintf(db, "_");
   if (may_fthru)
      if (flag & DoesFThru)
         fprintf(db, "t");
      else
         fprintf(db, "_");
  fprintf(db, " ");
  }

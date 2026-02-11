metadata_xrec_search(char *file, xrec_t *xrecs, int nrecs)
{
   int      ii, jj, kk, rkk;

   ii = nrecs / 2;
   jj = (ii + 1) / 2;
   nrecs--;
   rkk = 0;

   while (true)
   {
      kk = strcmp(xrecs[ii].file,file);

      if (kk > 0)
      {
         ii -= jj;
         if (ii < 0) return -1;
      }

      else if (kk < 0)
      {
         ii += jj;
         if (ii > nrecs) return -1;
      }

      else if (kk == 0) return ii;

      jj = jj / 2;

      if (jj == 0)
      {
         jj = 1;
         if (! rkk) rkk = kk;
         else
         {
            if (rkk > 0) { if (kk < 0) return -1; }
            else if (kk > 0) return -1;
         }
      }
   }
}

Solver(MatrixColX& mcout,
   const MatrixColX& mcin)
{
   REPORT
   int i = mcin.skip-mcout.skip; Real* elx = mcin.data-i;
   while (i-- > 0) *elx++ = 0.0;
   int nr = mcin.skip+mcin.storage;
   elx = mcin.data+mcin.storage; Real* el = elx;
   int j = mcout.skip+mcout.storage-nr;
   int nc = ncols_val-nr; i = nr-mcout.skip;
   while (j-- > 0) *elx++ = 0.0;
   Real* Ael = store + (nr*(2*ncols_val-nr+1))/2; j = 0;
   while (i-- > 0)
   {
      elx = el; Real sum = 0.0; int jx = j++; Ael -= nc;
      while (jx--) sum += *(--Ael) * *(--elx);
      elx--; *elx = (*elx - sum) / *(--Ael);
   }
}

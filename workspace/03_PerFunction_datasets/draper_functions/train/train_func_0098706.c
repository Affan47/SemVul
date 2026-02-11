SortSV(DiagonalMatrix& D, Matrix& U, bool ascending)
{
   REPORT
   Tracer trace("SortSV_DU");
   int m = U.Nrows(); int n = U.Ncols();
   if (n != D.Nrows()) Throw(IncompatibleDimensionsException(D,U));
   Real* u = U.Store();
   for (int i=0; i<n; i++)
   {
      int k = i; Real p = D.element(i);
      if (ascending)
      {
         for (int j=i+1; j<n; j++)
            { if (D.element(j) < p) { k = j; p = D.element(j); } }
      }
      else
      {
         for (int j=i+1; j<n; j++)
         { if (D.element(j) > p) { k = j; p = D.element(j); } }
      }
      if (k != i)
      {
         D.element(k) = D.element(i); D.element(i) = p; int j = m;
         Real* uji = u + i; Real* ujk = u + k;
         if (j) for(;;)
         {
            p = *uji; *uji = *ujk; *ujk = p;
            if (!(--j)) break;
            uji += n; ujk += n;
         }
      }
   }
}

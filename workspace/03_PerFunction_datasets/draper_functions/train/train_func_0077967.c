ComplexScale(RectMatrixCol& U, RectMatrixCol& V, Real x, Real y)
{
   REPORT
   int n = U.n;
   if (n != V.n)
   {
      Tracer tr("newmatrm");
      Throw(InternalException("Dimensions differ in ComplexScale"));
   }
   Real* u = U.store; Real* v = V.store;
   int su = U.spacing; int sv = V.spacing;


   if (n) for (;;)
   {
      Real z = *u * x - *v * y;  *v =  *u * y + *v * x;  *u = z;
      if (!(--n)) break;
      u += su;  v += sv;
   }
}

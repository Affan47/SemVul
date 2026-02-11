operator*(const RectMatrixRowCol& rmrc) const
{
   REPORT
   long_Real sum = 0.0; int i = n;
   Real* s = store; int d = spacing;
   Real* s1 = rmrc.store; int d1 = rmrc.spacing;
   if (i!=rmrc.n)
   {
      Tracer tr("newmatrm");
      Throw(InternalException("Dimensions differ in *"));
   }

   if (i) for(;;)
      { sum += (long_Real)*s * *s1; if (!(--i)) break; s += d; s1 += d1; }
   return (Real)sum;
}

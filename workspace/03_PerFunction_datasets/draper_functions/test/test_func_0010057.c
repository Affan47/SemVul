IsEqual(const GeneralMatrix& A) const
{
   Tracer tr("BandLUMatrix IsEqual");
   if (A.type() != type())
      { REPORT  return false; }
   if (&A == this)
      { REPORT  return true; }
   if ( A.Nrows() != nrows_val || A.Ncols() != ncols_val
      || ((BandLUMatrix&)A).m1 != m1 || ((BandLUMatrix&)A).m2 != m2 )

   { REPORT  return false; }


   REPORT
   return RealEqual(A.Store(),store,storage)
      && RealEqual(((BandLUMatrix&)A).store2,store2,storage2)
      && intEqual(((BandLUMatrix&)A).indx, indx, nrows_val);
}

infNorm() const
{
   register double norm = 0.0;
   register const double* elements = getElements();
   for (int i = getNumElements() - 1; i >= 0; --i) {
      norm = CoinMax(norm, fabs(elements[i]));
   }
   return norm;
}

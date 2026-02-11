Sum() const
{
   int i, j;
   double sum = 0.0;
   for(i=0; i<Rows(); i++)
      for(j=0; j<Cols(); j++)
         sum += (*mRowVec[i])[j];
   return sum;
}

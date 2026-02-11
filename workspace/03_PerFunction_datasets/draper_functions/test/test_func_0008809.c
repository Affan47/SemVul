setColLower(const double * array)
{
  int n=getNumCols();
  for (int i=0;i<n;i++)
    setColLower(i,array[i]);
}

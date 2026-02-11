Transpose(const double inElements[16],
                              double outElements[16])
{
  SqMatPtr inElem = (SqMatPtr)inElements;
  SqMatPtr outElem = (SqMatPtr)outElements;
  int i, j;
  double temp;

  for (i=0; i<4; i++)
    {
    for(j=i; j<4; j++)
      {
      temp = inElem[i][j];
      outElem[i][j] = inElem[j][i];
      outElem[j][i] = temp;
      }
    }
}

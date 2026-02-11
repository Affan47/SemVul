InsertRowVector(TMatrix X, TVector y, int row)
{
  int j, m;
  PRECISION *pX;
  if (!X || !y)
    {
      dw_Error(NULL_ERR);
      return (TMatrix)NULL;
    }
  if ((DimV(y) != ColM(X)) || (row < 0) || (RowM(X) <= row))
    {
      dw_Error(SIZE_ERR);
      return (TMatrix)NULL;
    }
  if (MajorForm(X))
    for (pX=pElementM(X)+(m=RowM(X))*(j=DimV(y)-1)+row; j >= 0; pX-=m, j--) *pX=ElementV(y,j);
  else
    memcpy(pElementM(X)+row*DimV(y),pElementV(y),DimV(y)*sizeof(PRECISION));
  return X;
}

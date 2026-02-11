Vec(TVector x, TMatrix Y)
{
  if (!Y)
    {
      dw_Error(NULL_ERR);
      return (TVector)NULL;
    }
  if (!x)
    {
      if (!(x=CreateVector(RowM(Y)*ColM(Y))))
	return (TVector)NULL;
    }
  else
    if (RowM(Y)*ColM(Y) != DimV(x))
      {
	dw_Error(SIZE_ERR);
	return (TVector)NULL;
      }
  if (MajorForm(Y))
    memcpy(pElementV(x),pElementM(Y),RowM(Y)*ColM(Y)*sizeof(PRECISION));
  else
    bTranspose(pElementV(x),pElementM(Y),RowM(Y),ColM(Y),0);
  return x;
}

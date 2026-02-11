CrossProduct_LU(TVector x, TMatrix Y)
{
  int i, j, sgn;
  PRECISION s;
  TMatrix X;
  TPermutation P;
  TVector z=(TVector)NULL;
  if (!Y)
    {
      dw_Error(NULL_ERR);
      return (TVector)NULL;
    }
  if (RowM(Y) != ColM(Y)+1)
    {
      dw_Error(SIZE_ERR);
      return (TVector)NULL;
    }
  if (!x)
    {
      if (!(z=x=CreateVector(RowM(Y))))
	return (TVector)NULL;
    }
  else
    if (RowM(Y) != DimV(x))
      {
	dw_Error(SIZE_ERR);
	return (TVector)NULL;
      }
  if (X=CreateMatrix(RowM(Y),ColM(Y)))
    {
      if (P=CreatePermutation(RowM(Y)))
	{
	  if (LU(P,X,Y))
	    {
	      ElementV(x,RowM(Y)-1)=1.0;
	      for (i=RowM(Y)-2; i >= 0; i--)
		{
		  ElementV(x,i)=0.0;
		  for (j=RowM(Y)-1; j > i; j--)
		    ElementV(x,i)-=ElementV(x,j)*ElementM(X,j,i);
		}
	      ProductTransposeVP(x,x,P);
	      for (sgn=1, i=RowM(X)-2; i >= 0; i--)
		if (ElementP(P,i) != i) sgn=-sgn;
	      for (s=0.0, i=RowM(X)-2; i >= 0; i--)
		if (ElementM(X,i,i) < 0.0)
		  {
		    s+=log(-ElementM(X,i,i));
		    sgn=-sgn;
		  }
		else
		  if (ElementM(X,i,i) > 0.0)
		    s+=log(ElementM(X,i,i));
		  else
		    break;
	      s=(i >= 0) ? 0.0 : sgn*exp(s);
	      ProductSV(x,s,x);
	    }
	  else
	    {
	      FreePermutation(P);
	      FreeMatrix(X);
	      if (z) FreeVector(z);
	      return (TVector)NULL;
	    }
	  FreePermutation(P);
	}
      FreeMatrix(X);
    }
  return x;
}

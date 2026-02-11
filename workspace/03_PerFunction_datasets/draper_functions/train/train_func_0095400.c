AbsV(TVector x, TVector y)
{
 if (!y)
  {
   dw_Error(NULL_ERR);
   return (TVector)NULL;
  }
 if (!x)
   {
    if (!(x=CreateVector(DimV(y))))
     return (TVector)NULL;
   }
  else
   if (DimV(x) != DimV(y))
    {
     dw_Error(SIZE_ERR);
     return (TVector)NULL;
    }
 bAbs(pElementV(x),pElementV(y),DimV(y));
 return x;
}

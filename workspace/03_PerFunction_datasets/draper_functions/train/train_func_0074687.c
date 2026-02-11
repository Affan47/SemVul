CreateVector(int m)
{
 TVector x;
 if (m <= 0)
  {
   dw_Error(SIZE_ERR);
   return (TVector)NULL;
  }
 if (x=(TVector)dw_malloc(sizeof(TVectorStructure)))
   if (x->x=(PRECISION*)dw_malloc(m*sizeof(PRECISION)))
     DimV(x)=m;
   else
     {
       dw_free(x);
       dw_Error(MEM_ERR);
       return (TVector)NULL;
     }
  else
   dw_Error(MEM_ERR);
 return x;
}

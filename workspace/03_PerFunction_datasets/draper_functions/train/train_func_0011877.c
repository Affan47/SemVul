Inverse_UT(TMatrix X, TMatrix T)
{
 PRECISION *ptr;
 int err;
 if (!T)
  {
   dw_Error(NULL_ERR);
   return (TMatrix)NULL;
  }
 if (RowM(T) != ColM(T))
  {
   dw_Error(SIZE_ERR);
   return (TMatrix)NULL;
  }
 if (!X)
   {
    if (X=IdentityMatrix(X,RowM(T)))
     if (err=bSolveTriangular(pElementM(T),pElementM(X),RowM(T),RowM(T),1,MajorForm(T),MajorForm(X)))
      {
       dw_Error(err);
       FreeMatrix(X);
       return (TMatrix)NULL;
      }
   }
  else
   if (X == T)
     {
      if (!(ptr=(PRECISION*)dw_malloc(RowM(T)*RowM(T)*sizeof(PRECISION))))
       {
        dw_Error(MEM_ERR);
        return (TMatrix)NULL;
       }
      memcpy(ptr,pElementM(T),RowM(T)*RowM(T)*sizeof(PRECISION));
      if (X=IdentityMatrix(X,RowM(T)))
       if (err=bSolveTriangular(ptr,pElementM(X),RowM(T),RowM(T),1,MajorForm(T),MajorForm(X)))
        {
         dw_Error(err);
         dw_free(ptr);
         return (TMatrix)NULL;
        }
      dw_free(ptr);
     }
    else
     if (X=IdentityMatrix(X,RowM(T)))
      if (err=bSolveTriangular(pElementM(T),pElementM(X),RowM(T),RowM(T),1,MajorForm(T),MajorForm(X)))
       {
        dw_Error(err);
        return (TMatrix)NULL;
       }
 return X;
}

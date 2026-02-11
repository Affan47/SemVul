Inverse_LU(TMatrix X, TMatrix Y)
{
 PRECISION *LU;
 int *p;
 TMatrix rtrn=(TMatrix)NULL;
 if (!Y)
   dw_Error(NULL_ERR);
  else
   if (RowM(Y) != ColM(Y))
     dw_Error(SIZE_ERR);
    else
     if (!(p=(int*)dw_malloc(RowM(Y)*sizeof(int))))
       dw_Error(MEM_ERR);
      else
       {
        if (!(LU=(PRECISION*)dw_malloc(RowM(Y)*RowM(Y)*sizeof(PRECISION))))
          dw_Error(MEM_ERR);
         else
          {
           memcpy(LU,pElementM(Y),RowM(Y)*RowM(Y)*sizeof(PRECISION));
           if (bLU(p,LU,RowM(Y),RowM(Y),MajorForm(Y)))
             dw_Error(SING_ERR);
            else
             if (rtrn=IdentityMatrix(X,RowM(Y)))
              {
               bPermutationMultiply(p,pElementM(rtrn),RowM(rtrn),ColM(rtrn),RowM(Y),1,MajorForm(rtrn));
               bSolveUnitTriangular(LU,pElementM(rtrn),RowM(rtrn),ColM(rtrn),0,MajorForm(Y),MajorForm(rtrn));
               bSolveTriangular(LU,pElementM(rtrn),RowM(rtrn),ColM(rtrn),1,MajorForm(Y),MajorForm(rtrn));
              }
           dw_free(LU);
          }
        dw_free(p);
       }
 return rtrn;
}

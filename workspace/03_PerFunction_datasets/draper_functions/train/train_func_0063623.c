SVD(TMatrix U, TVector d, TMatrix V, TMatrix A)
{
 int err, compact=1;
 if (!d || !A)
  {
   dw_Error(NULL_ERR);
   return 0;
  }
 if ((DimV(d) != ((RowM(A) < ColM(A)) ? RowM(A) : ColM(A))))
  {
   dw_Error(SIZE_ERR);
   return 0;
  }
 if (U)
   {
     if (U == V)
       {
	 dw_Error(ARG_ERR);
	 return 0;
       }
     if (RowM(U) != RowM(A))
       {
	 dw_Error(SIZE_ERR);
	 return 0;
       }
     if (ColM(U) != DimV(d))
       {
	 compact=0;
	 if (ColM(U) != RowM(U))
	   {
	     dw_Error(SIZE_ERR);
	     return 0;
	   }
       }
   }
 if (V)
   {
     if (RowM(V) != ColM(A))
       {
	 dw_Error(SIZE_ERR);
	 return 0;
       }
     if (ColM(V) != DimV(d))
       {
	 compact=0;
	 if (ColM(V) != RowM(V))
	   {
	     dw_Error(SIZE_ERR);
	     return 0;
	   }
       }
   }

 if (err=bSVD(U ? pElementM(U) : (PRECISION*)NULL,pElementV(d),V ? pElementM(V) : (PRECISION*)NULL,
	      pElementM(A),RowM(A),ColM(A),U ? MajorForm(U) : 1,V ? MajorForm(V) : 1,MajorForm(A),compact))
  {
    dw_Error(err);
    return 0;
  }
 return 1;
}

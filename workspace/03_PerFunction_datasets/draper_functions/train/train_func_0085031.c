ddf_UniqueRows(ddf_rowindex OV, long p, long r, ddf_Amatrix A, long dmax, ddf_rowset preferred, long *uniqrows)
{


  long i,iuniq,j;
  myfloat *x;
  ddf_boolean localdebug=ddf_FALSE;

  if (p<=0 || p > r) goto _L99;
  iuniq=p; j=1;
  x=A[p-1];
  OV[p]=j;
  for (i=p+1;i<=r; i++){
    if (!ddf_LexEqual(x,A[i-1],dmax)) {

      iuniq=i;
      j=j+1;
      OV[i]=j;
      x=A[i-1];
    } else {

      if (set_member(i, preferred) && !set_member(iuniq, preferred)){
        OV[iuniq]=-i;
        iuniq=i;
        OV[i]=j;
        x=A[i-1];
      } else {
        OV[i]=-iuniq;
      }
    }
  }
  *uniqrows=j;
  if (localdebug){
    printf("The number of unique rows are %ld\n with order vector",*uniqrows);
    for (i=p;i<=r; i++){
      printf(" %ld:%ld ",i,OV[i]);
    }
    printf("\n");
  }
  _L99:;
}

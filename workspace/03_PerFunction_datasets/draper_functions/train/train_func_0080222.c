PrintPermutation(FILE *f, TPermutation X)
{
 int i, j, k;
 for (i=0; i < DimP(X); i++)
  fprintf(f,"%3d ",i);
 fprintf(f,"\n");
 for (i=0; i < DimP(X); i++)
  {
    if (i < UseP(X))
      {
	k=ElementP(X,i);
	j=i-1;
      }
    else
      {
	k=i;
	j=UseP(X)-1;
      }
   for ( ; j >= 0; j--)
    if (k == ElementP(X,j)) k=j;
   fprintf(f,"%3d ",k);
  }
 fprintf(f,"\n");
}

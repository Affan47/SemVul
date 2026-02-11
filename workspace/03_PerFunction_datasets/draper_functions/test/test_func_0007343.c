ddf_MatrixNormalizedSortedUniqueCopy(ddf_MatrixPtr M,ddf_rowindex *newpos)
{


  ddf_MatrixPtr M1=NULL,M2=NULL;
  ddf_rowrange m,i;
  ddf_colrange d;
  ddf_rowindex newpos1=NULL,newpos1r=NULL,newpos2=NULL;


  m= M->rowsize;
  d= M->colsize;
  *newpos=(long *)calloc(m+1,sizeof(long));
  newpos1r=(long *)calloc(m+1,sizeof(long));
  if (m>=0 && d>=0){
    M1=ddf_MatrixNormalizedSortedCopy(M,&newpos1);
    for (i=1; i<=m;i++) newpos1r[newpos1[i]]=i;
    M2=ddf_MatrixUniqueCopy(M1,&newpos2);
    set_emptyset(M2->linset);
    for(i=1; i<=m; i++) {
      if (newpos2[newpos1[i]]>0){
         printf("newpos1[%ld]=%ld, newpos2[newpos1[%ld]]=%ld\n",i,newpos1[i], i,newpos2[newpos1[i]]);
         if (set_member(i,M->linset)) set_addelem(M2->linset, newpos2[newpos1[i]]);
         (*newpos)[i]=newpos2[newpos1[i]];
      } else {
         (*newpos)[i]=-newpos1r[-newpos2[newpos1[i]]];
      }
    }
  ddf_FreeMatrix(M1);free(newpos1);free(newpos2);free(newpos1r);
  }

  return M2;
}

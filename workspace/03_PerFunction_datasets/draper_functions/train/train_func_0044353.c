store_packed(A,B)
     struct blockmatrix A,B;
{
  int blk,i,j,n;
  double *p;
  double *q;

  for (blk=1; blk<=A.nblocks; blk++)
    {
      switch (A.blocks[blk].blockcategory)
	{
	case DIAG:
	  p=A.blocks[blk].data.vec;
	  q=B.blocks[blk].data.vec;
	  n=A.blocks[blk].blocksize;
	  for (i=1; i<=n; i++)
	    q[i]=p[i];
	  break;
	case MATRIX:
	  p=A.blocks[blk].data.mat;
	  q=B.blocks[blk].data.mat;
	  n=A.blocks[blk].blocksize;
#pragma omp parallel for schedule(dynamic,64) private(i,j) shared(p,q,n)
	  for (j=1; j<=n; j++)
	    for (i=1; i<=j; i++)
	      q[ijtokp(i,j,n)]=p[ijtok(i,j,n)];
	  break;
	default:
	  printf("store_packed illegal block type \n");
	  exit(12);
	};
    }

}

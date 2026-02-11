alloc_mat(A,pB)
     struct blockmatrix A;
     struct blockmatrix *pB;
{
  int blk;


  pB->nblocks=A.nblocks;


  pB->blocks=(struct blockrec *)malloc(sizeof(struct blockrec)*(A.nblocks+1));
  if (pB->blocks == NULL)
    {
      printf("Storage allocation failed!\n");
      exit(10);
    };


  for (blk=1; blk <=A.nblocks; blk++)
    {
      pB->blocks[blk].blockcategory=A.blocks[blk].blockcategory;
      pB->blocks[blk].blocksize=A.blocks[blk].blocksize;
      switch (A.blocks[blk].blockcategory)
	{
	case DIAG:
	  pB->blocks[blk].data.vec=(double *)malloc(sizeof(double)*(A.blocks[blk].blocksize+1));
	  if (pB->blocks[blk].data.vec == NULL)
	    {
	      printf("Storage allocation failed!\n");
	      exit(10);
	    };
	  break;
	case MATRIX:
	  pB->blocks[blk].data.mat=(double *)malloc(sizeof(double)*(A.blocks[blk].blocksize)*(A.blocks[blk].blocksize));
	  if (pB->blocks[blk].data.mat == NULL)
	    {
	      printf("Storage allocation failed!\n");
	      exit(10);
	    };
	  break;
	default:
	  printf("alloc_mat illegal block type!\n");
	  exit(12);
	};
    };
}

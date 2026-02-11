Fnorm(A)
     struct blockmatrix A;
{
  int blk;
  double nrm;
  double temp;

  nrm=0;
  for (blk=1; blk<=A.nblocks; blk++)
    {
      switch (A.blocks[blk].blockcategory)
	{
	case DIAG:
	  temp=norm2(A.blocks[blk].blocksize,A.blocks[blk].data.vec+1);
	  nrm += temp*temp;
	  break;
	case MATRIX:
	  temp=norm2(A.blocks[blk].blocksize*A.blocks[blk].blocksize,
		     A.blocks[blk].data.mat);
	  nrm += temp*temp;
	  break;
	case PACKEDMATRIX:
	default:
	  printf("Fnorm illegal block type \n");
	  exit(12);
	};
    };

  nrm=sqrt(nrm);
  return(nrm);
}

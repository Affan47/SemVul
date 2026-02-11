c_get_block_data_addr(int array, int block, int blkndx)
{
   long long ix;
   f_int farray, fblock, fblkndx, fstack;
#ifdef ALTIX
   double *a = dshptr;
#else
   double a[1];
#endif

   if (blkndx == -1)
   {
      printf("SERVER CALLED WITH BLKNDX -1\n");
      printf("array %d array_block %d\n",array,block);
      MPI_Abort(MPI_COMM_WORLD, 1);
   }

   farray = array;
   fblock = block;
   fblkndx = blkndx + 1;
   ix = F77_NAME(get_block_data_index, GET_BLOCK_DATA_INDEX) (&farray,
                   &fblock, &fstack, &fblkndx, &(a[0]));

   ix--;

   return ( &(a[ix]) );
}

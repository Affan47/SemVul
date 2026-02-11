lam_printfunc(void)
{
  int i, myrank;

  if (stack_size > 0) {
    myrank = lam_myproc->p_gps.gps_grank;
    printf("Rank (%d, MPI_COMM_WORLD): Call stack within LAM:\n", myrank);
    for (i = --stack_size; i >= 0; i--)
      printf("Rank (%d, MPI_COMM_WORLD):  - %s()\n", myrank,
	     blktype(func_stack[i]));
    printf("Rank (%d, MPI_COMM_WORLD):  - main()\n", myrank);
  }
}

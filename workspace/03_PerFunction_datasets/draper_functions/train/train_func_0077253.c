MPI_Testall_epilog (int count,
				MPI_Fint *reqs,
				int *flag,
				MPI_Status *s __attribute__((unused)),
				size_t size)
{
  if(*flag) {
    int i;
    for(i=0; i<count; i++)
      EZTRACE_EVENT1(FUT_MPI_TEST_SUCCESS, (void*)reqs + (i*size));
  }
}

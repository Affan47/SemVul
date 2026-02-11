MPI_Init(int * argc, char***argv)
{
  int ret = libMPI_Init(argc, argv);
  __mpi_init_generic();
  FUNCTION_ENTRY;
  return ret;
}

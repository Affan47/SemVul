MPI_Probe_epilog( int source __attribute__((unused)),
			      int tag __attribute__((unused)),
			      MPI_Comm comm __attribute__((unused)),
			      MPI_Status *status )
{
  int length = -1;
  MPI_Get_count(status, MPI_BYTE, &length);
  EZTRACE_EVENT3(FUT_MPI_STOP_PROBE, status->MPI_SOURCE, status->MPI_TAG, length);
}

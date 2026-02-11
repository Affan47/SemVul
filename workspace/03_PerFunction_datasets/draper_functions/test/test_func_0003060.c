MPIR_Status_set_bytes(MPI_Status *status, MPI_Datatype datatype,
                          int nbytes)
{


  if (datatype == MPI_DATATYPE_NULL);

  if (status != MPI_STATUS_IGNORE)
      status->st_length = nbytes;
  return MPI_SUCCESS;
}

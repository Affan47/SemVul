MPI_File_write_at(MPI_File fh, MPI_Offset offset, CONST void* buf,
                             VT_MPI_INT count, MPI_Datatype datatype,
                             MPI_Status* status)
{
  VT_MPI_INT result;
  uint32_t tid;

  GET_THREAD_ID(tid);

  if (IS_MPI_TRACE_ON(tid))
    {
      MPIIO_ENTER_IO_W_MATCHINGID_STATUS(VT__MPI_FILE_WRITE_AT);

      VT_UNIMCI_CHECK_PRE(MPI_File_write_at,
        (fh, offset, buf, count, datatype, status, "", 0, 0),
        was_recorded, &time);

      result = PMPI_File_write_at(fh, offset, buf, count, datatype, status);

      VT_UNIMCI_CHECK_POST(MPI_File_write_at,
        (fh, offset, buf, count, datatype, status, "", 0, 0),
        was_recorded, &time);

      MPIIO_LEAVE_IO_W_MATCHINGID_STATUS(VT_IOOP_WRITE);
    }
  else
    {
      result = PMPI_File_write_at(fh, offset, buf, count, datatype, status);
    }

  return result;
}

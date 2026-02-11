MPI_File_write_at_all_end(MPI_File fh, CONST void* buf,
                                     MPI_Status* status)
{
  VT_MPI_INT result;
  uint32_t tid;

  GET_THREAD_ID(tid);

  if (IS_MPI_TRACE_ON(tid))
    {
      MPIIO_ENTER_IO_W_STATUS(VT__MPI_FILE_WRITE_AT_ALL_END);

      VT_UNIMCI_CHECK_PRE(MPI_File_write_at_all_end,
        (fh, buf, status, "", 0, 0), was_recorded, &time);

      result = PMPI_File_write_at_all_end(fh, buf, status);

      VT_UNIMCI_CHECK_POST(MPI_File_write_at_all_end,
        (fh, buf, status, "", 0, 0), was_recorded, &time);

      MPIIO_LEAVE_IO_SPLITCOLL(VT_IOOP_WRITE | VT_IOFLAG_ASYNC | VT_IOFLAG_COLL);
    }
  else
    {
      result = PMPI_File_write_at_all_end(fh, buf, status);
    }

  return result;
}

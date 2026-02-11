MPI_File_write_ordered_begin(MPI_File fh, CONST void* buf,
                                        VT_MPI_INT count, MPI_Datatype datatype)
{
  VT_MPI_INT result;
  uint32_t tid;

  GET_THREAD_ID(tid);

  if (IS_MPI_TRACE_ON(tid))
    {
      MPIIO_ENTER_IO_SPLITCOLL(VT__MPI_FILE_WRITE_ORDERED_BEGIN);

      VT_UNIMCI_CHECK_PRE(MPI_File_write_ordered_begin,
        (fh, buf, count, datatype, "", 0, 0), was_recorded, &time);

      result = PMPI_File_write_ordered_begin(fh, buf, count, datatype);

      VT_UNIMCI_CHECK_POST(MPI_File_write_ordered_begin,
        (fh, buf, count, datatype, "", 0, 0), was_recorded, &time);

      MPIIO_LEAVE_IO();
    }
  else
    {
      result = PMPI_File_write_ordered_begin(fh, buf, count, datatype);
    }

  return result;
}

MPI_Send(CONST void* buf, VT_MPI_INT count, MPI_Datatype datatype,
                    VT_MPI_INT dest, VT_MPI_INT tag, MPI_Comm comm)
{
  VT_MPI_INT result;
  uint32_t tid;

  GET_THREAD_ID(tid);

  if (IS_MPI_TRACE_ON(tid))
    {
      uint64_t time;
      uint8_t was_recorded;

      MPI_TRACE_OFF(tid);

      time = vt_pform_wtime();
      was_recorded = vt_enter(tid, &time, vt_mpi_regid[VT__MPI_SEND]);

#if defined(HAVE_MPI2_THREAD) && HAVE_MPI2_THREAD
      if (!is_mpi_multithreaded)
#endif
        {
          if (dest != MPI_PROC_NULL && (was_recorded || env_mpi_ignore_filter))
            {
              VT_MPI_INT sz;
              PMPI_Type_size(datatype, &sz);
              vt_mpi_send(tid, &time, VT_RANK_TO_PE(dest, comm),
                          VT_COMM_ID(comm), tag, count * sz);
            }
        }

      VT_UNIMCI_CHECK_PRE(MPI_Send,
        (buf, count, datatype, dest, tag, comm, "", 0, 0), was_recorded, &time);

      result = PMPI_Send(buf, count, datatype, dest, tag, comm);

      VT_UNIMCI_CHECK_POST(MPI_Send,
        (buf, count, datatype, dest, tag, comm, "", 0, 0), was_recorded, &time);

      time = vt_pform_wtime();
      vt_exit(tid, &time);

      MPI_TRACE_ON(tid);
    }
  else
    {
      result = PMPI_Send(buf, count, datatype, dest, tag, comm);
    }

  return result;
}

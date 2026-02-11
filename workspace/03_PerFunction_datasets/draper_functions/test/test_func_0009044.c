MPI_Wait(MPI_Request* request, MPI_Status* status)
{
  VT_MPI_INT result;
  uint32_t tid;

  GET_THREAD_ID(tid);

  if (IS_MPI_TRACE_ON(tid))
    {
      uint64_t time;
      uint8_t was_recorded;

      MPI_Status mystatus;
      struct VTRequest* orig_req = NULL;

      MPI_TRACE_OFF(tid);

      time = vt_pform_wtime();
      was_recorded = vt_enter(tid, &time, vt_mpi_regid[VT__MPI_WAIT]);

#if defined(HAVE_MPI2_THREAD) && HAVE_MPI2_THREAD
      if (!is_mpi_multithreaded)
#endif
        {
          if (status == MPI_STATUS_IGNORE) status = &mystatus;
          orig_req = vt_request_get(*request);
        }

      VT_UNIMCI_CHECK_PRE(MPI_Wait,
        (request, status, "", 0, 0), was_recorded, &time);

      result = PMPI_Wait(request, status);

      VT_UNIMCI_CHECK_POST(MPI_Wait,
        (request, status, "", 0, 0), was_recorded, &time);

      time = vt_pform_wtime();

#if defined(HAVE_MPI2_THREAD) && HAVE_MPI2_THREAD
      if (!is_mpi_multithreaded)
#endif
        {
          vt_check_request(tid, &time, orig_req, status,
                           (was_recorded || env_mpi_ignore_filter));
        }

      vt_exit(tid, &time);

      MPI_TRACE_ON(tid);
    }
  else
    {
      result = PMPI_Wait(request, status);
    }

  return result;
}

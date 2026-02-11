vt_mpi_sync(uint32_t tid, uint64_t* time, void* comm)
{
#if (defined(VT_MPI) || defined(VT_HYB))
  static const int sync_flush_flag = 1<<0;
  static const int sync_time_flag  = 1<<1;
  static int sync_flush_env = -1;
  static int sync_flush_level_env = -1;
  static int sync_time_env = -1;
  static int sync_flush_skip = -1;
  VT_MPI_INT lsync_mask = 0;
  VT_MPI_INT sync_mask = 0;
  uint8_t was_recorded;

  GET_THREAD_ID(tid);


  if (sync_flush_env == -1)
    sync_flush_env = vt_env_sync_flush();
  if (sync_flush_level_env == -1)
    sync_flush_level_env = vt_env_sync_flush_level();
  if (sync_flush_skip == -1)
    sync_flush_skip = vt_env_sync_flush_skip();
#if (defined(VT_ETIMESYNC) && TIMER_IS_GLOBAL == 0)
  if (sync_time_env == -1)
    sync_time_env = vt_env_etimesync();
#else
  sync_time_env = 0;
#endif


  if (!sync_flush_env && !sync_time_env) return;


  if (*((MPI_Comm*)comm) != MPI_COMM_WORLD)
  {
    VT_MPI_INT comm_size;
    PMPI_Comm_size(*((MPI_Comm*)comm), &comm_size);
    if ((int)comm_size != vt_num_traces) return;
  }


  if (sync_flush_skip--) {
      return;
  }


  was_recorded = vt_enter(tid, time, vt_trc_regid[VT__TRC_SYNC]);


  if (sync_flush_env)
  {

    if ((int)VTGen_get_buflevel(VTTHRD_GEN(VTThrdv[tid])) >=
        sync_flush_level_env)
    {
      lsync_mask |= sync_flush_flag;

      if (sync_time_env) lsync_mask |= sync_time_flag;
    }
  }


#if (defined(VT_ETIMESYNC) && TIMER_IS_GLOBAL == 0)
  if (sync_time_env && (sync_mask & sync_time_flag) == 0)
  {

    if (vt_esync_next() <= *time)
      lsync_mask |= sync_time_flag;
  }
#endif

  PMPI_Allreduce(&lsync_mask, &sync_mask, 1,
                 MPI_INT, MPI_BOR, *((MPI_Comm*)comm));


  if ((sync_mask & sync_flush_flag) != 0)
    VTGen_flush(VTTHRD_GEN(VTThrdv[tid]), 0, vt_pform_wtime(), NULL);
#if (defined(VT_ETIMESYNC) && TIMER_IS_GLOBAL == 0)

  if ((sync_mask & sync_time_flag) != 0)
    vt_esync(*((MPI_Comm*)comm));
#endif


  if ((sync_mask & sync_time_flag) == 0 && (sync_mask & sync_flush_flag) != 0)
    PMPI_Barrier(*((MPI_Comm*)comm));


  *time = vt_pform_wtime();
  if (was_recorded)
  {
    vt_exit(tid, time);
  }
#endif
}

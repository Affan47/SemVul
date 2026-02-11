nbarrier_lin(struct _proc **procs, int nprocs)
{
  struct nmsg local, remote;
  int i;


  setup_nmsgs(&local, &remote);


  if (procs[0] != lam_myproc) {
    remote.nh_node = procs[0]->p_gps.gps_node;
    remote.nh_event = (-procs[0]->p_gps.gps_pid) & 0xBFFFFFFF;

    if (nsend(&remote) != 0) {
      return LAMERROR;
    }

    if (nrecv(&local) != 0) {
      return LAMERROR;
    }
  }


  else {
    for (i = 1; i < nprocs; ++i) {
      if (nrecv(&local) != 0) {
        return LAMERROR;
      }
    }

    for (i = 1; i < nprocs; ++i) {
      remote.nh_node = (procs[i])->p_gps.gps_node;
      remote.nh_event = (-(procs[i])->p_gps.gps_pid) & 0xBFFFFFFF;

      if (nsend(&remote) != 0) {
        return LAMERROR;
      }
    }
  }

  return 0;
}

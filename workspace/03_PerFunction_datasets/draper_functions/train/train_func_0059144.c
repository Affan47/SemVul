lamd_testany(MPI_Request req_top, int nreq_recv)
{
  struct bfsync *sel;
  MPI_Request req;
  int is_local;
  int xx_local;
  int xx_remote;
  int isel_ready;
  int r;


  xx_local = FALSE;
  xx_remote = FALSE;

  for (req = req_top; req; req = req->rq_next) {
    if (req->rq_state == LAM_RQSDONE)
      continue;

    if (req->rq_rpi->lmq_flags & LAMD_RECVMODE)
      continue;

    is_local = (req->rq_proc->p_gps.gps_node == LOCAL) ||
      (req->rq_proc->p_gps.gps_node == getnodeid());

    if (is_local && xx_local)
      continue;
    if (!is_local && xx_remote)
      continue;

    r = lamd_adv1(req, FALSE);

    if ((r < 0) || (r == 1))
      return (r);

    if (is_local) {
      xx_local = TRUE;
    } else {
      xx_remote = TRUE;
    }
  }


  if (nreq_recv == 0) {
    return (0);
  }


  do {
    lamd_preempt(FALSE);
    sel = lamd_fillsel(req_top, nreq_recv);

    if (sel == 0) {
      lamd_preempt(TRUE);
      return ((errno == EDEADNODE) ? 1 : LAMERROR);
    }

    lamd_noretry();
    r = bfiselect(sel, nreq_recv, KSYNCSQL, &isel_ready);
    free((char *) sel);
    lamd_retry();
  } while ((r < 0) && (errno == EINTR));

  if (r < 0)
    return (LAMERROR);


  if (isel_ready >= 0) {

    if (lamd_findfwd(req_top, isel_ready) < 0)
      return (LAMERROR);

    return (1);
  }

  return (0);
}

lamd_adv1(MPI_Request req, int flag_block)
{
  int r;
  int (*transfer) ();

  if (req->rq_type == LAM_RQIRECV) {
    transfer = lamd_recv;
  } else if (req->rq_type == LAM_RQIPROBE) {
    transfer = lamd_probe;
  } else {
    transfer = lamd_send;
  }


  do {
    lamd_preempt(FALSE);

    if (lamd_commdead(req)) {
      lamd_preempt(TRUE);
      return (1);
    }

    lamd_noretry();
    r = (*transfer) (req, flag_block);
    lamd_retry();
  } while ((r < 0) && (errno == EINTR));

  return (r);
}

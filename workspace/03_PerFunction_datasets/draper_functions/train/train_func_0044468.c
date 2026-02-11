lam_ssi_rpi_usysv_push_body_box(struct lam_ssi_rpi_proc *ps, MPI_Request req)
{
  volatile int *lock;
  double starttime = 0.0;
  int len;

  lock = &ps->cp_outbox->pb_header.bh_lock;
  if (lam_ssi_rpi_tcp_flblock) {


    if (req->rq_rpi->cq_nenvout > 0) {
      LAM_TRACE(starttime = ttime());
      spinlock(lock, 1, lam_ssi_rpi_usysv_lock_poll_write);
      LAM_TRACE(_kio.ki_blktime += (ttime() - starttime));

      ps->cp_outbox->pb_header.bh_env = req->rq_rpi->cq_env;

      if (req->rq_rpi->cq_nmsgout > 0) {
	len = LAM_min(req->rq_rpi->cq_nmsgout, lam_ssi_rpi_usysv_short);
	lam_memcpy(ps->cp_outbox + 1, req->rq_rpi->cq_msgbuf, len);
	req->rq_rpi->cq_msgbuf += len;
	req->rq_rpi->cq_nmsgout -= len;
      }

      SYNC_WRITE;
      *lock = 1;
      req->rq_rpi->cq_nenvout = 0;
    }

    while (req->rq_rpi->cq_nmsgout > 0) {
      spinlock(lock, 1, lam_ssi_rpi_usysv_lock_poll_write);
      len = LAM_min(req->rq_rpi->cq_nmsgout, lam_ssi_rpi_usysv_short);
      lam_memcpy(ps->cp_outbox + 1, req->rq_rpi->cq_msgbuf, len);

      SYNC_WRITE;
      *lock = 1;

      req->rq_rpi->cq_msgbuf += len;
      req->rq_rpi->cq_nmsgout -= len;
    }
  } else {


    if (req->rq_rpi->cq_nenvout > 0) {
      if (*lock == 1)
	return (0);

      ps->cp_outbox->pb_header.bh_env = req->rq_rpi->cq_env;

      if (req->rq_rpi->cq_nmsgout > 0) {
	len = LAM_min(req->rq_rpi->cq_nmsgout, lam_ssi_rpi_usysv_short);
	lam_memcpy(ps->cp_outbox + 1, req->rq_rpi->cq_msgbuf, len);
	req->rq_rpi->cq_msgbuf += len;
	req->rq_rpi->cq_nmsgout -= len;
      }

      SYNC_WRITE;
      *lock = 1;
      req->rq_rpi->cq_nenvout = 0;
    }

    while (req->rq_rpi->cq_nmsgout > 0) {
      if (*lock == 1)
	return (0);

      len = LAM_min(req->rq_rpi->cq_nmsgout, lam_ssi_rpi_usysv_short);
      lam_memcpy(ps->cp_outbox + 1, req->rq_rpi->cq_msgbuf, len);

      SYNC_WRITE;
      *lock = 1;

      req->rq_rpi->cq_msgbuf += len;
      req->rq_rpi->cq_nmsgout -= len;
    }
  }

  return (1);
}

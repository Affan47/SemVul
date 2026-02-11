crtcp_push_env(struct lam_ssi_rpi_proc *ps, MPI_Request req)
{
  int nbytes;

  nbytes = swrite(ps, req->rq_rpi->cq_envbuf, req->rq_rpi->cq_nenvout);
  if (nbytes > 0) {
    req->rq_rpi->cq_envbuf += nbytes;
    req->rq_rpi->cq_nenvout -= nbytes;
  }

  return (nbytes);
}

lam_ssi_rpi_crtcp_req_send_short(struct lam_ssi_rpi_proc *ps,
                               MPI_Request req)
{
  int nbytes;

  if ((nbytes = crtcp_push_body(ps, req)) <= 0) {
    return (nbytes);
  }

  req->rq_state = LAM_RQSACTIVE;

  if (req->rq_rpi->cq_nenvout == 0 && req->rq_rpi->cq_nmsgout == 0) {
    PUB(haveadv) = 1;
    ps->cp_wreq = 0;
    req->rq_state = LAM_RQSDONE;
    lam_rq_nactv--;
  }

  return (0);
}

writevcb(void *a, globus_io_handle_t *h, globus_result_t r,
	 struct iovec *iov, globus_size_t iovcnt, globus_size_t nb)

{
  IOMON	*monp = (IOMON *) a;

  globus_mutex_lock(&monp->mtx);
  monp->nb = nb;
  if (r != GLOBUS_SUCCESS)
    monp->rc = rrpc_globuserr(monp->errmsg, monp->errmsglen, r);
  monp->done = GLOBUS_TRUE;
  globus_cond_signal(&monp->cond);
  globus_mutex_unlock(&monp->mtx);
}

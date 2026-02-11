nlmsvc_proc_nm_lock(struct svc_rqst *rqstp, struct nlm_args *argp,
				            struct nlm_res  *resp)
{
	dprintk("lockd: NM_LOCK       called\n");

	argp->monitor = 0;
	return nlmsvc_proc_lock(rqstp, argp, resp);
}

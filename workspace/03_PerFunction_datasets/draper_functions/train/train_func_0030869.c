nfsd4_cb_probe_done(struct rpc_task *task, void *calldata)
{
	struct nfs4_client *clp = container_of(calldata, struct nfs4_client, cl_cb_null);

	if (task->tk_status)
		nfsd4_mark_cb_down(clp, task->tk_status);
	else
		clp->cl_cb_state = NFSD4_CB_UP;
}

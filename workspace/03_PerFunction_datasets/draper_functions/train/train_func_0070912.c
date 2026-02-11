nfs_initiate_pgio(struct rpc_clnt *clnt, struct nfs_pgio_header *hdr,
		      struct rpc_cred *cred, const struct nfs_rpc_ops *rpc_ops,
		      const struct rpc_call_ops *call_ops, int how, int flags)
{
	struct rpc_task *task;
	struct rpc_message msg = {
		.rpc_argp = &hdr->args,
		.rpc_resp = &hdr->res,
		.rpc_cred = cred,
	};
	struct rpc_task_setup task_setup_data = {
		.rpc_client = clnt,
		.task = &hdr->task,
		.rpc_message = &msg,
		.callback_ops = call_ops,
		.callback_data = hdr,
		.workqueue = nfsiod_workqueue,
		.flags = RPC_TASK_ASYNC | flags,
	};
	int ret = 0;

	hdr->rw_ops->rw_initiate(hdr, &msg, rpc_ops, &task_setup_data, how);

	dprintk("NFS: initiated pgio call "
		"(req %s/%llu, %u bytes @ offset %llu)\n",
		hdr->inode->i_sb->s_id,
		(unsigned long long)NFS_FILEID(hdr->inode),
		hdr->args.count,
		(unsigned long long)hdr->args.offset);

	task = rpc_run_task(&task_setup_data);
	if (IS_ERR(task)) {
		ret = PTR_ERR(task);
		goto out;
	}
	if (how & FLUSH_SYNC) {
		ret = rpc_wait_for_completion_task(task);
		if (ret == 0)
			ret = task->tk_status;
	}
	rpc_put_task(task);
out:
	return ret;
}

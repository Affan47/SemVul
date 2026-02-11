nfs41_walk_client_list(struct nfs_client *new,
			   struct nfs_client **result,
			   struct rpc_cred *cred)
{
	struct nfs_net *nn = net_generic(new->cl_net, nfs_net_id);
	struct nfs_client *pos, *prev = NULL;
	int status = -NFS4ERR_STALE_CLIENTID;

	spin_lock(&nn->nfs_client_lock);
	list_for_each_entry(pos, &nn->nfs_client_list, cl_share_link) {

		if (pos == new)
			goto found;

		if (pos->rpc_ops != new->rpc_ops)
			continue;

		if (pos->cl_minorversion != new->cl_minorversion)
			continue;


		if (pos->cl_cons_state > NFS_CS_READY) {
			atomic_inc(&pos->cl_count);
			spin_unlock(&nn->nfs_client_lock);

			nfs_put_client(prev);
			prev = pos;

			status = nfs_wait_client_init_complete(pos);
			spin_lock(&nn->nfs_client_lock);
			if (status < 0)
				break;
			status = -NFS4ERR_STALE_CLIENTID;
		}
		if (pos->cl_cons_state != NFS_CS_READY)
			continue;

		if (!nfs4_match_clientids(pos, new))
			continue;


		if (!nfs4_check_clientid_trunking(pos, new))
			continue;


		if (!nfs4_match_client_owner_id(pos, new))
			continue;
found:
		atomic_inc(&pos->cl_count);
		*result = pos;
		status = 0;
		dprintk("NFS: <-- %s using nfs_client = %p ({%d})\n",
			__func__, pos, atomic_read(&pos->cl_count));
		break;
	}

	spin_unlock(&nn->nfs_client_lock);
	dprintk("NFS: <-- %s status = %d\n", __func__, status);
	nfs_put_client(prev);
	return status;
}

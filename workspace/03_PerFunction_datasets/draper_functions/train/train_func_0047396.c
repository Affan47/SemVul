nfs4_callback_devicenotify(struct cb_devicenotifyargs *args,
				  void *dummy, struct cb_process_state *cps)
{
	int i;
	__be32 res = 0;
	struct nfs_client *clp = cps->clp;
	struct nfs_server *server = NULL;

	dprintk("%s: -->\n", __func__);

	if (!clp) {
		res = cpu_to_be32(NFS4ERR_OP_NOT_IN_SESSION);
		goto out;
	}

	for (i = 0; i < args->ndevs; i++) {
		struct cb_devicenotifyitem *dev = &args->devs[i];

		if (!server ||
		    server->pnfs_curr_ld->id != dev->cbd_layout_type) {
			rcu_read_lock();
			list_for_each_entry_rcu(server, &clp->cl_superblocks, client_link)
				if (server->pnfs_curr_ld &&
				    server->pnfs_curr_ld->id == dev->cbd_layout_type) {
					rcu_read_unlock();
					goto found;
				}
			rcu_read_unlock();
			dprintk("%s: layout type %u not found\n",
				__func__, dev->cbd_layout_type);
			continue;
		}

	found:
		nfs4_delete_deviceid(server->pnfs_curr_ld, clp, &dev->cbd_dev_id);
	}

out:
	kfree(args->devs);
	dprintk("%s: exit with status = %u\n",
		__func__, be32_to_cpu(res));
	return res;
}

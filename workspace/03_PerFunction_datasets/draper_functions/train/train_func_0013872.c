pnfs_destroy_layouts_byfsid(struct nfs_client *clp,
		struct nfs_fsid *fsid,
		bool is_recall)
{
	struct nfs_server *server;
	LIST_HEAD(layout_list);

	spin_lock(&clp->cl_lock);
	rcu_read_lock();
restart:
	list_for_each_entry_rcu(server, &clp->cl_superblocks, client_link) {
		if (memcmp(&server->fsid, fsid, sizeof(*fsid)) != 0)
			continue;
		if (pnfs_layout_bulk_destroy_byserver_locked(clp,
				server,
				&layout_list) != 0)
			goto restart;
	}
	rcu_read_unlock();
	spin_unlock(&clp->cl_lock);

	if (list_empty(&layout_list))
		return 0;
	return pnfs_layout_free_bulk_destroy_list(&layout_list, is_recall);
}

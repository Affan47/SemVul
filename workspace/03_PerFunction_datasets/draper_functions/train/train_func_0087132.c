afs_vnode_set_lock(struct afs_vnode *vnode, struct key *key,
		       afs_lock_type_t type)
{
	struct afs_server *server;
	int ret;

	_enter("%s{%x:%u.%u},%x,%u",
	       vnode->volume->vlocation->vldb.name,
	       vnode->fid.vid,
	       vnode->fid.vnode,
	       vnode->fid.unique,
	       key_serial(key), type);

	do {

		server = afs_volume_pick_fileserver(vnode);
		if (IS_ERR(server))
			goto no_server;

		_debug("USING SERVER: %08x\n", ntohl(server->addr.s_addr));

		ret = afs_fs_set_lock(server, key, vnode, type, &afs_sync_call);

	} while (!afs_volume_release_fileserver(vnode, server, ret));


	if (ret == 0)
		afs_put_server(server);

	_leave(" = %d", ret);
	return ret;

no_server:
	return PTR_ERR(server);
}

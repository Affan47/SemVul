afs_vnode_setattr(struct afs_vnode *vnode, struct key *key,
		      struct iattr *attr)
{
	struct afs_server *server;
	int ret;

	_enter("%s{%x:%u.%u},%x",
	       vnode->volume->vlocation->vldb.name,
	       vnode->fid.vid,
	       vnode->fid.vnode,
	       vnode->fid.unique,
	       key_serial(key));


	spin_lock(&vnode->lock);
	vnode->update_cnt++;
	spin_unlock(&vnode->lock);

	do {

		server = afs_volume_pick_fileserver(vnode);
		if (IS_ERR(server))
			goto no_server;

		_debug("USING SERVER: %08x\n", ntohl(server->addr.s_addr));

		ret = afs_fs_setattr(server, key, vnode, attr, &afs_sync_call);

	} while (!afs_volume_release_fileserver(vnode, server, ret));


	if (ret == 0) {
		afs_vnode_finalise_status_update(vnode, server);
		afs_put_server(server);
	} else {
		afs_vnode_status_update_failed(vnode, ret);
	}

	_leave(" = %d", ret);
	return ret;

no_server:
	spin_lock(&vnode->lock);
	vnode->update_cnt--;
	ASSERTCMP(vnode->update_cnt, >=, 0);
	spin_unlock(&vnode->lock);
	return PTR_ERR(server);
}

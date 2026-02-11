afs_vnode_cache_get_key(const void *cookie_netfs_data,
					void *buffer, uint16_t bufmax)
{
	const struct afs_vnode *vnode = cookie_netfs_data;
	uint16_t klen;

	_enter("{%x,%x,%llx},%p,%u",
	       vnode->fid.vnode, vnode->fid.unique, vnode->status.data_version,
	       buffer, bufmax);

	klen = sizeof(vnode->fid.vnode);
	if (klen > bufmax)
		return 0;

	memcpy(buffer, &vnode->fid.vnode, sizeof(vnode->fid.vnode));

	_leave(" = %u", klen);
	return klen;
}

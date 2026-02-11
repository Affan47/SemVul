afs_fs_setattr_size64(struct afs_server *server, struct key *key,
				 struct afs_vnode *vnode, struct iattr *attr,
				 const struct afs_wait_mode *wait_mode)
{
	struct afs_call *call;
	__be32 *bp;

	_enter(",%x,{%x:%u},,",
	       key_serial(key), vnode->fid.vid, vnode->fid.vnode);

	ASSERT(attr->ia_valid & ATTR_SIZE);

	call = afs_alloc_flat_call(&afs_RXFSStoreData64_as_Status,
				   (4 + 6 + 3 * 2) * 4,
				   (21 + 6) * 4);
	if (!call)
		return -ENOMEM;

	call->key = key;
	call->reply = vnode;
	call->service_id = FS_SERVICE;
	call->port = htons(AFS_FS_PORT);
	call->store_version = vnode->status.data_version + 1;
	call->operation_ID = FSSTOREDATA;


	bp = call->request;
	*bp++ = htonl(FSSTOREDATA64);
	*bp++ = htonl(vnode->fid.vid);
	*bp++ = htonl(vnode->fid.vnode);
	*bp++ = htonl(vnode->fid.unique);

	xdr_encode_AFS_StoreStatus(&bp, attr);

	*bp++ = 0;
	*bp++ = 0;
	*bp++ = 0;
	*bp++ = 0;
	*bp++ = htonl(attr->ia_size >> 32);
	*bp++ = htonl((u32) attr->ia_size);

	return afs_make_call(&server->addr, call, GFP_NOFS, wait_mode);
}

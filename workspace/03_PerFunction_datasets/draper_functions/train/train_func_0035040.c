afs_check_permit(struct afs_vnode *vnode, struct key *key,
			    afs_access_t *_access)
{
	struct afs_permits *permits;
	struct afs_permit *permit;
	struct afs_vnode *auth_vnode;
	bool valid;
	int loop, ret;

	_enter("{%x:%u},%x",
	       vnode->fid.vid, vnode->fid.vnode, key_serial(key));

	auth_vnode = afs_get_auth_inode(vnode, key);
	if (IS_ERR(auth_vnode)) {
		*_access = 0;
		_leave(" = %ld", PTR_ERR(auth_vnode));
		return PTR_ERR(auth_vnode);
	}

	ASSERT(S_ISDIR(auth_vnode->vfs_inode.i_mode));


	if (key == auth_vnode->volume->cell->anonymous_key) {
		_debug("anon");
		*_access = auth_vnode->status.anon_access;
		valid = true;
	} else {
		valid = false;
		rcu_read_lock();
		permits = rcu_dereference(auth_vnode->permits);
		if (permits) {
			permit = permits->permits;
			for (loop = permits->count; loop > 0; loop--) {
				if (permit->key == key) {
					_debug("found in cache");
					*_access = permit->access_mask;
					valid = true;
					break;
				}
				permit++;
			}
		}
		rcu_read_unlock();
	}

	if (!valid) {


		_debug("no valid permit");

		set_bit(AFS_VNODE_CB_BROKEN, &vnode->flags);
		ret = afs_vnode_fetch_status(vnode, auth_vnode, key);
		if (ret < 0) {
			iput(&auth_vnode->vfs_inode);
			*_access = 0;
			_leave(" = %d", ret);
			return ret;
		}
		*_access = vnode->status.caller_access;
	}

	iput(&auth_vnode->vfs_inode);
	_leave(" = 0 [access %x]", *_access);
	return 0;
}

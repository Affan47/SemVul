quota_statfs (call_frame_t *frame, xlator_t *this, loc_t *loc, dict_t *xdata)
{
	inode_t *root_inode = NULL;

	if (loc->inode) {
		root_inode = loc->inode->table->root;
		inode_ref(root_inode);
		STACK_WIND_COOKIE (frame, quota_statfs_cbk, root_inode,
				   FIRST_CHILD(this),
				   FIRST_CHILD(this)->fops->statfs, loc, xdata);
	}
	else {


		gf_log(this->name,GF_LOG_WARNING,
		       "missing inode, cannot adjust for quota");
		STACK_WIND (frame, default_statfs_cbk, FIRST_CHILD(this),
			    FIRST_CHILD(this)->fops->statfs, loc, xdata);
	}
        return 0;
}

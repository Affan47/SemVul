au_hn_alloc(struct au_hinode *hinode, struct inode *inode)
{
	int err;
	struct au_hnotify *hn;

	err = -ENOMEM;
	hn = au_cache_alloc_hnotify();
	if (hn) {
		hn->hn_aufs_inode = inode;
		hinode->hi_notify = hn;
		err = au_hnotify_op.alloc(hinode);
		AuTraceErr(err);
		if (unlikely(err)) {
			hinode->hi_notify = NULL;
			au_cache_free_hnotify(hn);


			if (err == -EEXIST)
				err = 0;
		}
	}

	AuTraceErr(err);
	return err;
}

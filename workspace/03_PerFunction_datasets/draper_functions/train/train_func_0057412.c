nfsd4_list_rec_dir(recdir_func *f, struct nfsd_net *nn)
{
	const struct cred *original_cred;
	struct dentry *dir = nn->rec_file->f_path.dentry;
	struct nfs4_dir_ctx ctx = {
		.ctx.actor = nfsd4_build_namelist,
		.names = LIST_HEAD_INIT(ctx.names)
	};
	struct name_list *entry, *tmp;
	int status;

	status = nfs4_save_creds(&original_cred);
	if (status < 0)
		return status;

	status = vfs_llseek(nn->rec_file, 0, SEEK_SET);
	if (status < 0) {
		nfs4_reset_creds(original_cred);
		return status;
	}

	status = iterate_dir(nn->rec_file, &ctx.ctx);
	mutex_lock_nested(&d_inode(dir)->i_mutex, I_MUTEX_PARENT);

	list_for_each_entry_safe(entry, tmp, &ctx.names, list) {
		if (!status) {
			struct dentry *dentry;
			dentry = lookup_one_len(entry->name, dir, HEXDIR_LEN-1);
			if (IS_ERR(dentry)) {
				status = PTR_ERR(dentry);
				break;
			}
			status = f(dir, dentry, nn);
			dput(dentry);
		}
		list_del(&entry->list);
		kfree(entry);
	}
	mutex_unlock(&d_inode(dir)->i_mutex);
	nfs4_reset_creds(original_cred);

	list_for_each_entry_safe(entry, tmp, &ctx.names, list) {
		dprintk("NFSD: %s. Left entry %s\n", __func__, entry->name);
		list_del(&entry->list);
		kfree(entry);
	}
	return status;
}

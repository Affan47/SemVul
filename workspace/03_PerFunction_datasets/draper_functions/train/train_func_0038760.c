au_reval_and_lock_fdi(struct file *file, int (*reopen)(struct file *file),
			  int wlock)
{
	int err;
	unsigned int sigen, figen;
	aufs_bindex_t bstart;
	unsigned char pseudo_link;
	struct dentry *dentry;
	struct inode *inode;

	err = 0;
	dentry = file->f_path.dentry;
	inode = d_inode(dentry);
	sigen = au_sigen(dentry->d_sb);
	fi_write_lock(file);
	figen = au_figen(file);
	di_write_lock_child(dentry);
	bstart = au_dbstart(dentry);
	pseudo_link = (bstart != au_ibstart(inode));
	if (sigen == figen && !pseudo_link && au_fbstart(file) == bstart) {
		if (!wlock) {
			di_downgrade_lock(dentry, AuLock_IR);
			fi_downgrade_lock(file);
		}
		goto out;
	}

	AuDbg("sigen %d, figen %d\n", sigen, figen);
	if (au_digen_test(dentry, sigen)) {
		err = au_reval_dpath(dentry, sigen);
		AuDebugOn(!err && au_digen_test(dentry, sigen));
	}

	if (!err)
		err = refresh_file(file, reopen);
	if (!err) {
		if (!wlock) {
			di_downgrade_lock(dentry, AuLock_IR);
			fi_downgrade_lock(file);
		}
	} else {
		di_write_unlock(dentry);
		fi_write_unlock(file);
	}

out:
	return err;
}

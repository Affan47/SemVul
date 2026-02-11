v9fs_mmap_file_mmap(struct file *filp, struct vm_area_struct *vma)
{
	int retval;
	struct inode *inode;
	struct v9fs_inode *v9inode;
	struct p9_fid *fid;

	inode = file_inode(filp);
	v9inode = V9FS_I(inode);
	mutex_lock(&v9inode->v_mutex);
	if (!v9inode->writeback_fid &&
	    (vma->vm_flags & VM_WRITE)) {


		fid = v9fs_writeback_fid(file_dentry(filp));
		if (IS_ERR(fid)) {
			retval = PTR_ERR(fid);
			mutex_unlock(&v9inode->v_mutex);
			return retval;
		}
		v9inode->writeback_fid = (void *) fid;
	}
	mutex_unlock(&v9inode->v_mutex);

	retval = generic_file_mmap(filp, vma);
	if (!retval)
		vma->vm_ops = &v9fs_mmap_file_vm_ops;

	return retval;
}

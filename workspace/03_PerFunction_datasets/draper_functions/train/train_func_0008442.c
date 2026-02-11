f2fs_file_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct inode *inode = file_inode(file);

	if (f2fs_encrypted_inode(inode)) {
		int err = f2fs_get_encryption_info(inode);
		if (err)
			return 0;
	}


	if (f2fs_has_inline_data(inode)) {
		int err = f2fs_convert_inline_inode(inode);
		if (err)
			return err;
	}

	file_accessed(file);
	vma->vm_ops = &f2fs_file_vm_ops;
	return 0;
}

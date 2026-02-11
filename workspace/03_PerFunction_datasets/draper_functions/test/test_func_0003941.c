v9fs_vm_page_mkwrite(struct vm_area_struct *vma, struct vm_fault *vmf)
{
	struct v9fs_inode *v9inode;
	struct page *page = vmf->page;
	struct file *filp = vma->vm_file;
	struct inode *inode = file_inode(filp);


	p9_debug(P9_DEBUG_VFS, "page %p fid %lx\n",
		 page, (unsigned long)filp->private_data);


	file_update_time(filp);

	v9inode = V9FS_I(inode);

	v9fs_fscache_wait_on_page_write(inode, page);
	BUG_ON(!v9inode->writeback_fid);
	lock_page(page);
	if (page->mapping != inode->i_mapping)
		goto out_unlock;
	wait_for_stable_page(page);

	return VM_FAULT_LOCKED;
out_unlock:
	unlock_page(page);
	return VM_FAULT_NOPAGE;
}

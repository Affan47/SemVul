ocfs2_osb_debug_open(struct inode *inode, struct file *file)
{
	struct ocfs2_super *osb = inode->i_private;
	char *buf = NULL;

	buf = kmalloc(PAGE_SIZE, GFP_KERNEL);
	if (!buf)
		goto bail;

	i_size_write(inode, ocfs2_osb_dump(osb, buf, PAGE_SIZE));

	file->private_data = buf;

	return 0;
bail:
	return -ENOMEM;
}

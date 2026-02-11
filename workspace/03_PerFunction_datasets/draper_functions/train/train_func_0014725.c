vcs_open(struct inode *inode, struct file *filp)
{
	unsigned int currcons = iminor(inode) & 127;
	int ret = 0;

	console_lock();
	if(currcons && !vc_cons_allocated(currcons-1))
		ret = -ENXIO;
	console_unlock();
	return ret;
}

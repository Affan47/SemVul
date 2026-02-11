tm6000_mmap(struct file *file, struct vm_area_struct * vma)
{
	struct tm6000_fh *fh = file->private_data;
	struct tm6000_core *dev = fh->dev;
	int res;

	if (mutex_lock_interruptible(&dev->lock))
		return -ERESTARTSYS;
	res = videobuf_mmap_mapper(&fh->vb_vidq, vma);
	mutex_unlock(&dev->lock);
	return res;
}

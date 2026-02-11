bttv_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct bttv_fh *fh = file->private_data;

	dprintk("%d: mmap type=%s 0x%lx+%ld\n",
		fh->btv->c.nr, v4l2_type_names[fh->type],
		vma->vm_start, vma->vm_end - vma->vm_start);
	return videobuf_mmap_mapper(bttv_queue(fh),vma);
}

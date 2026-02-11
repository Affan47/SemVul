zoran_vm_close (struct vm_area_struct *vma)
{
	struct zoran_mapping *map = vma->vm_private_data;
	struct zoran_fh *fh = map->fh;
	struct zoran *zr = fh->zr;
	int i;

	dprintk(3, KERN_INFO "%s: %s - munmap(%s)\n", ZR_DEVNAME(zr),
		__func__, mode_name(fh->map_mode));

	for (i = 0; i < fh->buffers.num_buffers; i++) {
		if (fh->buffers.buffer[i].map == map)
			fh->buffers.buffer[i].map = NULL;
	}
	kfree(map);


	for (i = 0; i < fh->buffers.num_buffers; i++) {
		if (fh->buffers.buffer[i].map) {
			return;
		}
	}

	dprintk(3, KERN_INFO "%s: %s - free %s buffers\n", ZR_DEVNAME(zr),
		__func__, mode_name(fh->map_mode));

	if (fh->map_mode == ZORAN_MAP_MODE_RAW) {
		if (fh->buffers.active != ZORAN_FREE) {
			unsigned long flags;

			spin_lock_irqsave(&zr->spinlock, flags);
			zr36057_set_memgrab(zr, 0);
			zr->v4l_buffers.allocated = 0;
			zr->v4l_buffers.active = fh->buffers.active = ZORAN_FREE;
			spin_unlock_irqrestore(&zr->spinlock, flags);
		}
		v4l_fbuffer_free(fh);
	} else {
		if (fh->buffers.active != ZORAN_FREE) {
			jpg_qbuf(fh, -1, zr->codec_mode);
			zr->jpg_buffers.allocated = 0;
			zr->jpg_buffers.active = fh->buffers.active = ZORAN_FREE;
		}
		jpg_fbuffer_free(fh);
	}
}

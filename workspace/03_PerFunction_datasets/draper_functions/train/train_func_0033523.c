snd_us428ctls_mmap(struct snd_hwdep * hw, struct file *filp, struct vm_area_struct *area)
{
	unsigned long	size = (unsigned long)(area->vm_end - area->vm_start);
	struct usX2Ydev	*us428 = hw->private_data;


 	if (!(us428->chip_status & USX2Y_STAT_CHIP_INIT))
		return -EBUSY;


        if (size > PAGE_ALIGN(sizeof(struct us428ctls_sharedmem))) {
		snd_printd( "%lu > %lu\n", size, (unsigned long)sizeof(struct us428ctls_sharedmem));
                return -EINVAL;
	}

	if (!us428->us428ctls_sharedmem) {
		init_waitqueue_head(&us428->us428ctls_wait_queue_head);
		if(!(us428->us428ctls_sharedmem = snd_malloc_pages(sizeof(struct us428ctls_sharedmem), GFP_KERNEL)))
			return -ENOMEM;
		memset(us428->us428ctls_sharedmem, -1, sizeof(struct us428ctls_sharedmem));
		us428->us428ctls_sharedmem->CtlSnapShotLast = -2;
	}
	area->vm_ops = &us428ctls_vm_ops;
	area->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP;
	area->vm_private_data = hw->private_data;
	return 0;
}

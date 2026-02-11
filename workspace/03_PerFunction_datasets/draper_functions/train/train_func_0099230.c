kfd_mmap(struct file *filp, struct vm_area_struct *vma)
{
	struct kfd_process *process;

	process = kfd_get_process(current);
	if (IS_ERR(process))
		return PTR_ERR(process);

	if ((vma->vm_pgoff & KFD_MMAP_DOORBELL_MASK) ==
			KFD_MMAP_DOORBELL_MASK) {
		vma->vm_pgoff = vma->vm_pgoff ^ KFD_MMAP_DOORBELL_MASK;
		return kfd_doorbell_mmap(process, vma);
	} else if ((vma->vm_pgoff & KFD_MMAP_EVENTS_MASK) ==
			KFD_MMAP_EVENTS_MASK) {
		vma->vm_pgoff = vma->vm_pgoff ^ KFD_MMAP_EVENTS_MASK;
		return kfd_event_mmap(process, vma);
	}

	return -EFAULT;
}

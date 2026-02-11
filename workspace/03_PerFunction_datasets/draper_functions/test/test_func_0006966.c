stm_char_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct stm_file *stmf = file->private_data;
	struct stm_device *stm = stmf->stm;
	unsigned long size, phys;

	if (!stm->data->mmio_addr)
		return -EOPNOTSUPP;

	if (vma->vm_pgoff)
		return -EINVAL;

	size = vma->vm_end - vma->vm_start;

	if (stmf->output.nr_chans * stm->data->sw_mmiosz != size)
		return -EINVAL;

	phys = stm->data->mmio_addr(stm->data, stmf->output.master,
				    stmf->output.channel,
				    stmf->output.nr_chans);

	if (!phys)
		return -EINVAL;

	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	vma->vm_flags |= VM_IO | VM_DONTEXPAND | VM_DONTDUMP;
	vm_iomap_memory(vma, phys, size);

	return 0;
}

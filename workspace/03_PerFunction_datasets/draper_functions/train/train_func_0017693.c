psbfb_mmap(struct fb_info *info, struct vm_area_struct *vma)
{
	struct psb_fbdev *fbdev = info->par;
	struct psb_framebuffer *psbfb = &fbdev->pfb;

	if (vma->vm_pgoff != 0)
		return -EINVAL;
	if (vma->vm_pgoff > (~0UL >> PAGE_SHIFT))
		return -EINVAL;

	if (!psbfb->addr_space)
		psbfb->addr_space = vma->vm_file->f_mapping;


	vma->vm_ops = &psbfb_vm_ops;
	vma->vm_private_data = (void *)psbfb;
	vma->vm_flags |= VM_IO | VM_MIXEDMAP | VM_DONTEXPAND | VM_DONTDUMP;
	return 0;
}

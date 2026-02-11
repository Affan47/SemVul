mlx5_ib_mmap(struct ib_ucontext *ibcontext, struct vm_area_struct *vma)
{
	struct mlx5_ib_ucontext *context = to_mucontext(ibcontext);
	struct mlx5_ib_dev *dev = to_mdev(ibcontext->device);
	struct mlx5_uuar_info *uuari = &context->uuari;
	unsigned long command;
	unsigned long idx;
	phys_addr_t pfn;

	command = get_command(vma->vm_pgoff);
	switch (command) {
	case MLX5_IB_MMAP_REGULAR_PAGE:
		if (vma->vm_end - vma->vm_start != PAGE_SIZE)
			return -EINVAL;

		idx = get_index(vma->vm_pgoff);
		if (idx >= uuari->num_uars)
			return -EINVAL;

		pfn = uar_index2pfn(dev, uuari->uars[idx].index);
		mlx5_ib_dbg(dev, "uar idx 0x%lx, pfn 0x%llx\n", idx,
			    (unsigned long long)pfn);

		vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);
		if (io_remap_pfn_range(vma, vma->vm_start, pfn,
				       PAGE_SIZE, vma->vm_page_prot))
			return -EAGAIN;

		mlx5_ib_dbg(dev, "mapped WC at 0x%lx, PA 0x%llx\n",
			    vma->vm_start,
			    (unsigned long long)pfn << PAGE_SHIFT);
		break;

	case MLX5_IB_MMAP_GET_CONTIGUOUS_PAGES:
		return -ENOSYS;

	default:
		return -EINVAL;
	}

	return 0;
}

scif_munmap(struct vm_area_struct *vma)
{
	struct scif_endpt *ep;
	struct vma_pvt *vmapvt = vma->vm_private_data;
	int nr_pages = (vma->vm_end - vma->vm_start) >> PAGE_SHIFT;
	s64 offset;
	struct scif_rma_req req;
	struct scif_window *window = NULL;
	int err;

	might_sleep();
	dev_dbg(scif_info.mdev.this_device,
		"SCIFAPI munmap: vma_start 0x%lx vma_end 0x%lx\n",
		vma->vm_start, vma->vm_end);
	ep = vmapvt->ep;
	offset = vmapvt->valid_offset ? vmapvt->offset :
		(vma->vm_pgoff) << PAGE_SHIFT;
	dev_dbg(scif_info.mdev.this_device,
		"SCIFAPI munmap: ep %p nr_pages 0x%x offset 0x%llx\n",
		ep, nr_pages, offset);
	req.out_window = &window;
	req.offset = offset;
	req.nr_bytes = vma->vm_end - vma->vm_start;
	req.prot = vma->vm_flags & (VM_READ | VM_WRITE);
	req.type = SCIF_WINDOW_PARTIAL;
	req.head = &ep->rma_info.remote_reg_list;

	mutex_lock(&ep->rma_info.rma_lock);

	err = scif_query_window(&req);
	if (err)
		dev_err(scif_info.mdev.this_device,
			"%s %d err %d\n", __func__, __LINE__, err);
	else
		scif_rma_list_munmap(window, offset, nr_pages);

	mutex_unlock(&ep->rma_info.rma_lock);


	vma->vm_ops = NULL;
	vma->vm_private_data = NULL;
	kref_put(&vmapvt->ref, vma_pvt_release);
	scif_delete_vma(ep, vma);
}

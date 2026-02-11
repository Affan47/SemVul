amdgpu_ih_ring_init(struct amdgpu_device *adev, unsigned ring_size,
			bool use_bus_addr)
{
	u32 rb_bufsz;
	int r;


	rb_bufsz = order_base_2(ring_size / 4);
	ring_size = (1 << rb_bufsz) * 4;
	adev->irq.ih.ring_size = ring_size;
	adev->irq.ih.ptr_mask = adev->irq.ih.ring_size - 1;
	adev->irq.ih.rptr = 0;
	adev->irq.ih.use_bus_addr = use_bus_addr;

	if (adev->irq.ih.use_bus_addr) {
		if (!adev->irq.ih.ring) {


			adev->irq.ih.ring = pci_alloc_consistent(adev->pdev,
								 adev->irq.ih.ring_size + 8,
								 &adev->irq.ih.rb_dma_addr);
			if (adev->irq.ih.ring == NULL)
				return -ENOMEM;
			memset((void *)adev->irq.ih.ring, 0, adev->irq.ih.ring_size + 8);
			adev->irq.ih.wptr_offs = (adev->irq.ih.ring_size / 4) + 0;
			adev->irq.ih.rptr_offs = (adev->irq.ih.ring_size / 4) + 1;
		}
		return 0;
	} else {
		r = amdgpu_wb_get(adev, &adev->irq.ih.wptr_offs);
		if (r) {
			dev_err(adev->dev, "(%d) ih wptr_offs wb alloc failed\n", r);
			return r;
		}

		r = amdgpu_wb_get(adev, &adev->irq.ih.rptr_offs);
		if (r) {
			amdgpu_wb_free(adev, adev->irq.ih.wptr_offs);
			dev_err(adev->dev, "(%d) ih rptr_offs wb alloc failed\n", r);
			return r;
		}

		return amdgpu_ih_ring_alloc(adev);
	}
}

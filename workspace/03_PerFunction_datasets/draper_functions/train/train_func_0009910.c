ion_cma_allocate(struct ion_heap *heap, struct ion_buffer *buffer,
			    unsigned long len, unsigned long align,
			    unsigned long flags)
{
	struct ion_cma_heap *cma_heap = to_cma_heap(heap);
	struct device *dev = cma_heap->dev;
	struct ion_cma_buffer_info *info;

	dev_dbg(dev, "Request buffer allocation len %ld\n", len);

	if (buffer->flags & ION_FLAG_CACHED)
		return -EINVAL;

	if (align > PAGE_SIZE)
		return -EINVAL;

	info = kzalloc(sizeof(struct ion_cma_buffer_info), GFP_KERNEL);
	if (!info)
		return ION_CMA_ALLOCATE_FAILED;

	info->cpu_addr = dma_alloc_coherent(dev, len, &(info->handle),
						GFP_HIGHUSER | __GFP_ZERO);

	if (!info->cpu_addr) {
		dev_err(dev, "Fail to allocate buffer\n");
		goto err;
	}

	info->table = kmalloc(sizeof(struct sg_table), GFP_KERNEL);
	if (!info->table)
		goto free_mem;

	if (dma_get_sgtable(dev, info->table, info->cpu_addr, info->handle,
			    len))
		goto free_table;

	buffer->priv_virt = info;
	dev_dbg(dev, "Allocate buffer %p\n", buffer);
	return 0;

free_table:
	kfree(info->table);
free_mem:
	dma_free_coherent(dev, len, info->cpu_addr, info->handle);
err:
	kfree(info);
	return ION_CMA_ALLOCATE_FAILED;
}

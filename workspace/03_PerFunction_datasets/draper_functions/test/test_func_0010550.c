mthca_buf_alloc(struct mthca_dev *dev, int size, int max_direct,
		    union mthca_buf *buf, int *is_direct, struct mthca_pd *pd,
		    int hca_write, struct mthca_mr *mr)
{
	int err = -ENOMEM;
	int npages, shift;
	u64 *dma_list = NULL;
	dma_addr_t t;
	int i;

	if (size <= max_direct) {
		*is_direct = 1;
		npages     = 1;
		shift      = get_order(size) + PAGE_SHIFT;

		buf->direct.buf = dma_alloc_coherent(&dev->pdev->dev,
						     size, &t, GFP_KERNEL);
		if (!buf->direct.buf)
			return -ENOMEM;

		dma_unmap_addr_set(&buf->direct, mapping, t);

		memset(buf->direct.buf, 0, size);

		while (t & ((1 << shift) - 1)) {
			--shift;
			npages *= 2;
		}

		dma_list = kmalloc(npages * sizeof *dma_list, GFP_KERNEL);
		if (!dma_list)
			goto err_free;

		for (i = 0; i < npages; ++i)
			dma_list[i] = t + i * (1 << shift);
	} else {
		*is_direct = 0;
		npages     = (size + PAGE_SIZE - 1) / PAGE_SIZE;
		shift      = PAGE_SHIFT;

		dma_list = kmalloc(npages * sizeof *dma_list, GFP_KERNEL);
		if (!dma_list)
			return -ENOMEM;

		buf->page_list = kmalloc(npages * sizeof *buf->page_list,
					 GFP_KERNEL);
		if (!buf->page_list)
			goto err_out;

		for (i = 0; i < npages; ++i)
			buf->page_list[i].buf = NULL;

		for (i = 0; i < npages; ++i) {
			buf->page_list[i].buf =
				dma_alloc_coherent(&dev->pdev->dev, PAGE_SIZE,
						   &t, GFP_KERNEL);
			if (!buf->page_list[i].buf)
				goto err_free;

			dma_list[i] = t;
			dma_unmap_addr_set(&buf->page_list[i], mapping, t);

			clear_page(buf->page_list[i].buf);
		}
	}

	err = mthca_mr_alloc_phys(dev, pd->pd_num,
				  dma_list, shift, npages,
				  0, size,
				  MTHCA_MPT_FLAG_LOCAL_READ |
				  (hca_write ? MTHCA_MPT_FLAG_LOCAL_WRITE : 0),
				  mr);
	if (err)
		goto err_free;

	kfree(dma_list);

	return 0;

err_free:
	mthca_buf_free(dev, size, buf, *is_direct, NULL);

err_out:
	kfree(dma_list);

	return err;
}

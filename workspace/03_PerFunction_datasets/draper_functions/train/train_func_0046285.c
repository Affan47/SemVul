mthca_buf_free(struct mthca_dev *dev, int size, union mthca_buf *buf,
		    int is_direct, struct mthca_mr *mr)
{
	int i;

	if (mr)
		mthca_free_mr(dev, mr);

	if (is_direct)
		dma_free_coherent(&dev->pdev->dev, size, buf->direct.buf,
				  dma_unmap_addr(&buf->direct, mapping));
	else {
		for (i = 0; i < (size + PAGE_SIZE - 1) / PAGE_SIZE; ++i)
			dma_free_coherent(&dev->pdev->dev, PAGE_SIZE,
					  buf->page_list[i].buf,
					  dma_unmap_addr(&buf->page_list[i],
							 mapping));
		kfree(buf->page_list);
	}
}

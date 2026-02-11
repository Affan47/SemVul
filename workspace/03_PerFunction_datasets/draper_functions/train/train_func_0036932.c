cnic_alloc_bnx2x_context(struct cnic_dev *dev)
{
	struct cnic_local *cp = dev->cnic_priv;
	struct bnx2x *bp = netdev_priv(dev->netdev);
	int ctx_blk_size = cp->ethdev->ctx_blk_size;
	int total_mem, blks, i;

	total_mem = BNX2X_CONTEXT_MEM_SIZE * cp->max_cid_space;
	blks = total_mem / ctx_blk_size;
	if (total_mem % ctx_blk_size)
		blks++;

	if (blks > cp->ethdev->ctx_tbl_len)
		return -ENOMEM;

	cp->ctx_arr = kcalloc(blks, sizeof(struct cnic_ctx), GFP_KERNEL);
	if (cp->ctx_arr == NULL)
		return -ENOMEM;

	cp->ctx_blks = blks;
	cp->ctx_blk_size = ctx_blk_size;
	if (!CHIP_IS_E1(bp))
		cp->ctx_align = 0;
	else
		cp->ctx_align = ctx_blk_size;

	cp->cids_per_blk = ctx_blk_size / BNX2X_CONTEXT_MEM_SIZE;

	for (i = 0; i < blks; i++) {
		cp->ctx_arr[i].ctx =
			dma_alloc_coherent(&dev->pcidev->dev, cp->ctx_blk_size,
					   &cp->ctx_arr[i].mapping,
					   GFP_KERNEL);
		if (cp->ctx_arr[i].ctx == NULL)
			return -ENOMEM;

		if (cp->ctx_align && cp->ctx_blk_size == ctx_blk_size) {
			if (cp->ctx_arr[i].mapping & (cp->ctx_align - 1)) {
				cnic_free_context(dev);
				cp->ctx_blk_size += cp->ctx_align;
				i = -1;
				continue;
			}
		}
	}
	return 0;
}

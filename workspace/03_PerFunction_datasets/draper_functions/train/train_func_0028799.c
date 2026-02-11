mga_dma_init(struct drm_device *dev, void *data,
		 struct drm_file *file_priv)
{
	drm_mga_init_t *init = data;
	int err;

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	switch (init->func) {
	case MGA_INIT_DMA:
		err = mga_do_init_dma(dev, init);
		if (err)
			(void)mga_do_cleanup_dma(dev, FULL_CLEANUP);
		return err;
	case MGA_CLEANUP_DMA:
		return mga_do_cleanup_dma(dev, FULL_CLEANUP);
	}

	return -EINVAL;
}

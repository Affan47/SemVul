virtgpu_gem_prime_import_sg_table(
	struct drm_device *dev, struct dma_buf_attachment *attach,
	struct sg_table *table)
{
	WARN_ONCE(1, "not implemented");
	return ERR_PTR(-ENODEV);
}

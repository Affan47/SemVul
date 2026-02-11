i915_guc_submission_init(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	const size_t ctxsize = sizeof(struct guc_context_desc);
	const size_t poolsize = GUC_MAX_GPU_CONTEXTS * ctxsize;
	const size_t gemsize = round_up(poolsize, PAGE_SIZE);
	struct intel_guc *guc = &dev_priv->guc;

	if (!i915.enable_guc_submission)
		return 0;

	if (guc->ctx_pool_obj)
		return 0;

	guc->ctx_pool_obj = gem_allocate_guc_obj(dev_priv->dev, gemsize);
	if (!guc->ctx_pool_obj)
		return -ENOMEM;

	spin_lock_init(&dev_priv->guc.host2guc_lock);

	ida_init(&guc->ctx_ids);

	guc_create_log(guc);

	return 0;
}

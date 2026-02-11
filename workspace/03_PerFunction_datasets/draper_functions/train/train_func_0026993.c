__create_hw_context(struct drm_device *dev,
		    struct drm_i915_file_private *file_priv)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_context *ctx;
	int ret;

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (ctx == NULL)
		return ERR_PTR(-ENOMEM);

	kref_init(&ctx->ref);
	list_add_tail(&ctx->link, &dev_priv->context_list);
	ctx->i915 = dev_priv;

	if (dev_priv->hw_context_size) {
		struct drm_i915_gem_object *obj =
				i915_gem_alloc_context_obj(dev, dev_priv->hw_context_size);
		if (IS_ERR(obj)) {
			ret = PTR_ERR(obj);
			goto err_out;
		}
		ctx->legacy_hw_ctx.rcs_state = obj;
	}


	if (file_priv != NULL) {
		ret = idr_alloc(&file_priv->context_idr, ctx,
				DEFAULT_CONTEXT_HANDLE, 0, GFP_KERNEL);
		if (ret < 0)
			goto err_out;
	} else
		ret = DEFAULT_CONTEXT_HANDLE;

	ctx->file_priv = file_priv;
	ctx->user_handle = ret;


	ctx->remap_slice = (1 << NUM_L3_SLICES(dev)) - 1;

	ctx->hang_stats.ban_period_seconds = DRM_I915_CTX_BAN_PERIOD;

	return ctx;

err_out:
	i915_gem_context_unreference(ctx);
	return ERR_PTR(ret);
}

free_pd(struct drm_device *dev, struct i915_page_directory *pd)
{
	if (px_page(pd)) {
		cleanup_px(dev, pd);
		kfree(pd->used_pdes);
		kfree(pd);
	}
}

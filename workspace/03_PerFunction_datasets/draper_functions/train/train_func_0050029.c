__pdp_init(struct drm_device *dev,
		      struct i915_page_directory_pointer *pdp)
{
	size_t pdpes = I915_PDPES_PER_PDP(dev);

	pdp->used_pdpes = kcalloc(BITS_TO_LONGS(pdpes),
				  sizeof(unsigned long),
				  GFP_KERNEL);
	if (!pdp->used_pdpes)
		return -ENOMEM;

	pdp->page_directory = kcalloc(pdpes, sizeof(*pdp->page_directory),
				      GFP_KERNEL);
	if (!pdp->page_directory) {
		kfree(pdp->used_pdpes);


		pdp->used_pdpes = NULL;
		return -ENOMEM;
	}

	return 0;
}

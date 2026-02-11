psb_gtt_alloc_range(struct drm_device *dev, int len,
				      const char *name, int backed, u32 align)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	struct gtt_range *gt;
	struct resource *r = dev_priv->gtt_mem;
	int ret;
	unsigned long start, end;

	if (backed) {

		start = r->start;
		end = r->start + dev_priv->gtt.stolen_size - 1;
	} else {

		start = r->start + dev_priv->gtt.stolen_size;
		end = r->end;
	}

	gt = kzalloc(sizeof(struct gtt_range), GFP_KERNEL);
	if (gt == NULL)
		return NULL;
	gt->resource.name = name;
	gt->stolen = backed;
	gt->in_gart = backed;
	gt->roll = 0;

	gt->gem.dev = dev;
	ret = allocate_resource(dev_priv->gtt_mem, &gt->resource,
				len, start, end, align, NULL, NULL);
	if (ret == 0) {
		gt->offset = gt->resource.start - r->start;
		return gt;
	}
	kfree(gt);
	return NULL;
}

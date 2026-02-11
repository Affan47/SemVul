gf100_fb_new_(const struct nvkm_fb_func *func, struct nvkm_device *device,
	      int index, struct nvkm_fb **pfb)
{
	struct gf100_fb *fb;

	if (!(fb = kzalloc(sizeof(*fb), GFP_KERNEL)))
		return -ENOMEM;
	nvkm_fb_ctor(func, device, index, &fb->base);
	*pfb = &fb->base;

	fb->r100c10_page = alloc_page(GFP_KERNEL | __GFP_ZERO);
	if (fb->r100c10_page) {
		fb->r100c10 = dma_map_page(device->dev, fb->r100c10_page, 0,
					   PAGE_SIZE, DMA_BIDIRECTIONAL);
		if (dma_mapping_error(device->dev, fb->r100c10))
			return -EFAULT;
	}

	return 0;
}

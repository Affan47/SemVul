nouveau_vga_font_io(struct drm_device *dev,
				void __iomem *iovram,
				bool save, unsigned plane)
{
	unsigned i;

	NVWriteVgaSeq(dev, 0, NV_VIO_SR_PLANE_MASK_INDEX, 1 << plane);
	NVWriteVgaGr(dev, 0, NV_VIO_GX_READ_MAP_INDEX, plane);
	for (i = 0; i < 16384; i++) {
		if (save) {
			nv04_display(dev)->saved_vga_font[plane][i] =
					ioread32_native(iovram + i * 4);
		} else {
			iowrite32_native(nv04_display(dev)->saved_vga_font[plane][i],
							iovram + i * 4);
		}
	}
}

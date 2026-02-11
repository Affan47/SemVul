fz_fill_image_mask(fz_device *dev, fz_image *image, fz_matrix ctm,
	fz_colorspace *colorspace, float *color, float alpha)
{
	if (dev->fill_image_mask)
		dev->fill_image_mask(dev, image, ctm, colorspace, color, alpha);
}

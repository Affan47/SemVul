prepare(int mode) {
	int color_type = png_get_color_type(m_PNGPtr, m_InfoPtr);
	if (color_type == PNG_COLOR_TYPE_PALETTE) {

		int num_palette;
		png_colorp palette;
		png_get_PLTE(m_PNGPtr, m_InfoPtr, &palette, &num_palette);
		rgb* pal = allocPalette(num_palette);
		for (int i = 0; i < num_palette; i++) {
			pal[i].red = palette[i].red;
			pal[i].green = palette[i].green;
			pal[i].blue = palette[i].blue;
		}
		setNbColors(num_palette);
		setMode(GLE_BITMAP_INDEXED);
		setComponents(1);
		if (m_BitsPerComponent < 8) {
			png_set_packing(m_PNGPtr);
		}
		checkGrayScalePalette();
	} else if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {

		setMode(GLE_BITMAP_GRAYSCALE);
		setComponents(1);
	} else {

		setMode(GLE_BITMAP_RGB);
		setComponents(3);
	}
	if (color_type & PNG_COLOR_MASK_ALPHA) {
		setAlpha(true);
		setComponents(getComponents() + 1);
		setExtraComponents(1);
	}
	return GLE_IMAGE_ERROR_NONE;
}

updateImageType() {
	if (getNbColors() == 0) {
		setMode(GLE_BITMAP_GRAYSCALE);
	} else {
		setMode(GLE_BITMAP_INDEXED);
		setBitsPerComponent(getMaxBits());
		checkGrayScalePalette();
	}
}

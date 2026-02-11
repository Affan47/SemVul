SetRGBAImage(Point sizeRGBAImage, const unsigned char *pixelsRGBAImage) {
	delete image;
	image = new RGBAImage(sizeRGBAImage.x, sizeRGBAImage.y, pixelsRGBAImage);
	markType = SC_MARK_RGBAIMAGE;
}

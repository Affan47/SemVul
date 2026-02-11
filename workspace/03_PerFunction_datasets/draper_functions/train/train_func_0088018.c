gdImageDestroy(gdImagePtr im)
{
	int i;
	for (i=0; (i<im->sx); i++) {
		free(im->pixels[i]);
	}
	free(im->pixels);
	if (im->polyInts) {
			free(im->polyInts);
	}
	if (im->style) {
		free(im->style);
	}
	free(im);
}

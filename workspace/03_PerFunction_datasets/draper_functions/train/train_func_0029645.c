df_libgd_get_pixel(int i, int j, int component)
{
    static int pixel;
    int alpha;

    switch(component) {
    case 0:	pixel = gdImageGetTrueColorPixel(im, i,j);
    		return gdTrueColorGetRed(pixel);
    case 1:	return gdTrueColorGetGreen(pixel);
    case 2:	return gdTrueColorGetBlue(pixel);
    case 3:
		alpha = 2 * gdTrueColorGetAlpha(pixel);
		return (255-alpha);
    default:	return 0;
    }
}

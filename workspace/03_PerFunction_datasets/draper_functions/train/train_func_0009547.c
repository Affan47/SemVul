Extract_Plane(in_image, out_image, plane)
    register XImage *in_image, *out_image;
    int plane;
{
    register int x, y;

    for (y = 0; y < in_image->height; y++)
	for (x = 0; x < in_image->width; x++)
	    XPutPixel(out_image, x, y,
		      (XGetPixel(in_image, x, y) >> plane) & 1);
}

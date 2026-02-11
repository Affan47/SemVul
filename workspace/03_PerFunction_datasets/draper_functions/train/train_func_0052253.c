image_merge_cmyk(IMAGE *img, IMAGE *layer, float cyan, float magenta,
   float yellow, float black)
{
    int x;
    int y;
    unsigned char *img_row;
    unsigned char *layer_row;
    unsigned char *p;
    int img_topfirst;
    int layer_topfirst;
    unsigned int val;
    if ((img == NULL) || (img->image == NULL))
	return -1;
    if ((layer == NULL) || (layer->image == NULL))
	return -1;
    if ((img->format & DISPLAY_COLORS_MASK) != DISPLAY_COLORS_CMYK)
	return -1;
    if ((img->format & DISPLAY_DEPTH_MASK) != DISPLAY_DEPTH_8)
	return -1;
    if ((img->format & DISPLAY_ENDIAN_MASK) != DISPLAY_BIGENDIAN)
	return -1;
    if ((layer->format & DISPLAY_COLORS_MASK) != DISPLAY_COLORS_GRAY)
	return -1;
    if ((layer->format & DISPLAY_DEPTH_MASK) != DISPLAY_DEPTH_8)
	return -1;
    if (img->width != layer->width)
	return -1;
    if (img->height != layer->height)
	return -1;

    img_topfirst = ((img->format & DISPLAY_FIRSTROW_MASK) == DISPLAY_TOPFIRST);
    layer_topfirst = ((layer->format & DISPLAY_FIRSTROW_MASK)
	== DISPLAY_TOPFIRST);

    for (y=0; y<(int)img->height; y++) {
        img_row = img->image + img->raster *
	    (img_topfirst ? y : ((int)img->height - y - 1));
        layer_row = layer->image + layer->raster *
	    (layer_topfirst ? y : ((int)layer->height - y - 1));
	for (x=0; x<(int)img->width; x++) {
	    val = layer_row[x];
	    p = &img_row[x*4];
	    p[0] = (unsigned char)min(255, p[0] + (255-val) * cyan);
	    p[1] = (unsigned char)min(255, p[1] + (255-val) * magenta);
	    p[2] = (unsigned char)min(255, p[2] + (255-val) * yellow);
	    p[3] = (unsigned char)min(255, p[3] + (255-val) * black);
	}
    }
    return 0;
}

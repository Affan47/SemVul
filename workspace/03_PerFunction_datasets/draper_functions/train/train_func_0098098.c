orient_page(struct ps_spec *spec)
{
    int mode = PORTRAIT;
    int pagewidth_in_pixels;
    int pageheight_in_pixels;
    int badfit = 0;
    float wx, wy;
    float aspect;
    float page_aspect;

    if (!spec->width_dpi) {
	wx = spec->page_width - 2*spec->page_margin;
	wy = spec->page_height - 2*spec->page_margin;
	page_aspect = wy/wx;
	aspect = spec->image_height*1.0/spec->image_width;
	if ((aspect>1 && page_aspect>1) || (aspect<1 && page_aspect<1)) {
	    spec->width_dpi = spec->image_width/wx;
	    spec->height_dpi = spec->image_height/wy;
	} else {
	    spec->width_dpi = spec->image_height/wx;
	    spec->height_dpi = spec->image_width/wy;
	}
    }

    pagewidth_in_pixels = spec->width_dpi * spec->page_width;
    pageheight_in_pixels = spec->height_dpi * spec->page_height;

    if (spec->image_width > pagewidth_in_pixels) {
        if (spec->image_height < pageheight_in_pixels) {
            mode = LANDSCAPE;
        } else
            badfit = 1;
    } else if (spec->image_height > pageheight_in_pixels) {
        if (spec->image_width < pagewidth_in_pixels) {
            mode = PORTRAIT;
        } else
            badfit = 1;
    }

    if (badfit)
        DXWarning("PostScript image overflows page");

    if (spec->page_orient == ORIENT_NOT_SET || spec->page_orient == ORIENT_AUTO)
        spec->page_orient = mode;

}

gdgen_set_penstyle(GVJ_t * job, gdImagePtr im, gdImagePtr brush)
{
    obj_state_t *obj = job->obj;
    int i, pen, width, dashstyle[40];

    if (obj->pen == PEN_DASHED) {
	for (i = 0; i < 10; i++)
	    dashstyle[i] = obj->pencolor.u.index;
	for (; i < 20; i++)
	    dashstyle[i] = gdTransparent;
	gdImageSetStyle(im, dashstyle, 20);
	pen = gdStyled;
    } else if (obj->pen == PEN_DOTTED) {
	for (i = 0; i < 2; i++)
	    dashstyle[i] = obj->pencolor.u.index;
	for (; i < 14; i++)
	    dashstyle[i] = gdTransparent;
	gdImageSetStyle(im, dashstyle, 12);
	pen = gdStyled;
    } else {
	pen = obj->pencolor.u.index;
    }

    width = obj->penwidth * job->zoom;
    if (width < PENWIDTH_NORMAL)
	width = PENWIDTH_NORMAL;
    gdImageSetThickness(im, width);

    if (width != PENWIDTH_NORMAL) {
	if (im->trueColor) {
	    brush = gdImageCreateTrueColor(width,width);
	}
	else {
	    brush = gdImageCreate(width, width);
	    gdImagePaletteCopy(brush, im);
	}
	gdImageFilledRectangle(brush, 0, 0, width - 1, width - 1,
			       obj->pencolor.u.index);
	gdImageSetBrush(im, brush);
	if (pen == gdStyled)
	    pen = gdStyledBrushed;
	else
	    pen = gdBrushed;
    }

    return pen;
}

AllocShadowColors(ShadowWidget w, XColor *col)
{
    Display	*disp = XtDisplay(w);
    Colormap	cmap = w->core.colormap;
    XColor	sh_col;

    if ((col->red > 0xefff && col->green > 0xefff && col->blue > 0xefff) ||
	(col->red < 0x1000 && col->green < 0x1000 && col->blue < 0x1000)) {
	sh_col.red   = 65535L * 4 / 5;
        sh_col.green = 65535L * 4 / 5;
        sh_col.blue  = 65535L * 4 / 5;
        if (!XAllocColor(disp, cmap, &sh_col))
	    return False;
	w->shadow.light_pixel = sh_col.pixel;

        sh_col.red   = 65535L * 3 /5;
        sh_col.green = 65535L * 3 /5;
        sh_col.blue  = 65535L * 3 /5;
        if (!XAllocColor(disp, cmap, &sh_col)) {
	    unsigned long	tmp = w->shadow.light_pixel;

	    XFreeColors(disp, cmap, &tmp, 1, 0);
	    return False;
	}
        w->shadow.dark_pixel = sh_col.pixel;
    } else {
        sh_col.red   = MIN (65535, 6 * (long)col->red   / 5);
        sh_col.green = MIN (65535, 6 * (long)col->green / 5);
        sh_col.blue  = MIN (65535, 6 * (long)col->blue  / 5);
        if (!XAllocColor(disp, cmap, &sh_col))
	    return False;
        w->shadow.light_pixel = sh_col.pixel;

        sh_col.red   = MIN (65535, 3 * (long)col->red   / 5);
        sh_col.green = MIN (65535, 3 * (long)col->green / 5);
        sh_col.blue  = MIN (65535, 3 * (long)col->blue  / 5);
        if (!XAllocColor(disp, cmap, &sh_col)) {
	    unsigned long	tmp = w->shadow.light_pixel;

	    XFreeColors(disp, cmap, &tmp, 1, 0);
	    return False;
	}
        w->shadow.dark_pixel = sh_col.pixel;
    }

    return True;
}

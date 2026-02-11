MakeIconWindow(GXDisplay *gdisp, GXWindow pixmap) {
    XSetWindowAttributes attrs;
    unsigned long wmask = 0;

    if ( !gdisp->default_visual ) {
	attrs.colormap = gdisp->cmap;
	wmask |= CWColormap;
    }
    wmask |= CWBackPixmap;
    attrs.background_pixmap = pixmap->w;
return( XCreateWindow(gdisp->display, gdisp->root,
	    0, 0, pixmap->pos.width, pixmap->pos.height,
	    0,
	    gdisp->depth, InputOutput, gdisp->visual, wmask, &attrs));
}

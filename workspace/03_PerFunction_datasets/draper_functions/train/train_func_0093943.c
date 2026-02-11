FindAllColors(GXDisplay *gdisp, XColor *x_colors) {
    int i;

    for ( i=0; i<(1<<gdisp->depth); ++i )
	x_colors[i].pixel = i;
    XQueryColors(gdisp->display,gdisp->cmap,x_colors,1<<gdisp->depth);
return( 1<<gdisp->depth );
}

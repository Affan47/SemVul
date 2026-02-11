sort_into_grid(const gdouble *points, guint pointlen, guint npoints,
               const GridInfo *ginfo)
{
    GSList **grid = g_new0(GSList*, ginfo->xres*ginfo->yres);
    gdouble xq = ginfo->xres/ginfo->xreal, xo = ginfo->xoff;
    gdouble yq = ginfo->yres/ginfo->yreal, yo = ginfo->yoff;
    guint i;

    for (i = 0; i < npoints; i++) {
        gdouble x = points[i*pointlen], y = points[i*pointlen + 1];
        guint xi = (guint)floor(xq*(x - xo)), yi = (guint)floor(yq*(y - yo));
        guint k = yi*ginfo->xres + xi;

        grid[k] = g_slist_prepend(grid[k], GUINT_TO_POINTER(i));
    }

    return grid;
}

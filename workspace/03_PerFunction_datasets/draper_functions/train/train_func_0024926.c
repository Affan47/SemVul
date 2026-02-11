plot_click(t_gobj *z, t_glist *glist,
    t_word *data, t_template *template, t_scalar *sc, t_array *ap,
    t_float basex, t_float basey,
    int xpix, int ypix, int shift, int alt, int dbl, int doit)
{
    t_plot *x = (t_plot *)z;
    t_symbol *elemtemplatesym;
    t_float linewidth, xloc, xinc, yloc, style, vis, scalarvis;
    t_array *array;
    t_fielddesc *xfielddesc, *yfielddesc, *wfielddesc;

    if (!plot_readownertemplate(x, data, template,
        &elemtemplatesym, &array, &linewidth, &xloc, &xinc, &yloc, &style,
        &vis, &scalarvis,
        &xfielddesc, &yfielddesc, &wfielddesc) && (vis != 0))
    {
        return (array_doclick(array, glist, sc, ap,
            elemtemplatesym,
            linewidth, basex + xloc, xinc, basey + yloc, scalarvis,
            xfielddesc, yfielddesc, wfielddesc,
            xpix, ypix, shift, alt, dbl, doit));
    }
    else return (0);
}

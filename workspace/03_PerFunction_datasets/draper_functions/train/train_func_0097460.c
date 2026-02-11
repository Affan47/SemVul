svg_curveto(gx_device_vector *vdev, floatp x0, floatp y0,
            floatp x1, floatp y1, floatp x2, floatp y2,
            floatp x3, floatp y3, gx_path_type_t type)
{
    gx_device_svg *svg = (gx_device_svg *)vdev;
    char line[SVG_LINESIZE];


    if (svg->page_count)
      return 0;


    if (!(type & gx_path_type_fill) && !(type & gx_path_type_stroke))
      return 0;

    if_debug8m('_', svg->memory, "svg_curveto(%lf,%lf, %lf,%lf, %lf,%lf, %lf,%lf) ",
        x0,y0, x1,y1, x2,y2, x3,y3);
    svg_print_path_type(svg, type);
    if_debug0m('_', svg->memory, "\n");

    gs_sprintf(line, " C%lf,%lf %lf,%lf %lf,%lf", x1,y1, x2,y2, x3,y3);
    svg_write(svg, line);

    return 0;
}

xps_dorect(gx_device_vector *vdev, fixed x0, fixed y0,
           fixed x1, fixed y1, gx_path_type_t type)
{
    gx_device_xps *xps = (gx_device_xps *)vdev;
    char line[300];
    const char *fmt;
    gx_color_index c;

    (void)gdev_vector_stream((gx_device_vector*)xps);

    if_debug9m('_', xps->memory,
               "rect type=%d coords=%g,%g %g,%g %g,%g %g,%g\n", type,
                fixed2float(x0), fixed2float(y0),
                fixed2float(x0), fixed2float(y1),
                fixed2float(x1), fixed2float(y1),
                fixed2float(x1), fixed2float(y0));


    if (!drawing_path(type)) {
        gs_warn1("xps_rect: type not supported %x", type);
        return 0;
    }

    if ((type & gx_path_type_stroke) && !xps->can_stroke) {
        return_error(gs_error_rangecheck);
    }

    write_str_to_current_page(xps, "<Path ");

    if (type & gx_path_type_fill) {

        fmt = "Fill=\"#%06X\" Data=\"M %g, %g L %g, %g %g, %g %g, %g Z\" ";
        c = xps->fillcolor & 0xffffffL;
        gs_sprintf(line, fmt, c,
                fixed2float(x0), fixed2float(y0),
                fixed2float(x0), fixed2float(y1),
                fixed2float(x1), fixed2float(y1),
                fixed2float(x1), fixed2float(y0));
    } else {
        fmt = "Stroke=\"#%06X\" Data=\"M %g, %g L %g, %g %g, %g %g, %g Z\" ";
        c = xps->strokecolor & 0xffffffL;
        gs_sprintf(line, fmt, c,
                fixed2float(x0), fixed2float(y0),
                fixed2float(x0), fixed2float(y1),
                fixed2float(x1), fixed2float(y1),
                fixed2float(x1), fixed2float(y0));
    }

    write_str_to_current_page(xps, line);

    if (type & gx_path_type_stroke) {

        fmt = "StrokeThickness=\"%g\" ";
        gs_sprintf(line, fmt, xps->linewidth);
        write_str_to_current_page(xps, line);
    }

    return write_str_to_current_page(xps, "/>\n");
}

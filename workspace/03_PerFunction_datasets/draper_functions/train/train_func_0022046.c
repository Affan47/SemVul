xps_beginpage(gx_device_vector *vdev)
{

    gx_device_xps *xps = (gx_device_xps *)vdev;
    char buf[128];
    int code = 0;

    if_debug0m('_', xps->memory, "xps_beginpage\n");

    {
        const char *template = "<PageContent Source=\"Pages/%d.fpage\" />";

        code = gs_sprintf(buf, template, xps->page_count + 1);
        if (code < 0)
            return gs_rethrow_code(code);


        code = write_str_to_zip_file(xps, "Documents/1/FixedDocument.fdoc", buf);
        if (code < 0)
            return gs_rethrow_code(code);

    }

    {
        const char *page_size_template = "<FixedPage Width=\"%d\" Height=\"%d\" "
            "xmlns=\"http://schemas.microsoft.com/xps/2005/06\" xml:lang=\"en-US\">\n";
        code = gs_sprintf(buf, page_size_template,
                       (int)(xps->MediaSize[0] * 4.0/3.0),
                       (int)(xps->MediaSize[1] * 4.0/3.0));
        if (code < 0)
            return gs_rethrow_code(code);
        code = write_str_to_current_page(xps, buf);
        if (code < 0)
            return gs_rethrow_code(code);
    }
    {
        const char *canvas_template = "<Canvas RenderTransform=\"%g,%g,%g,%g,%g,%g\">\n";
        code = gs_sprintf(buf, canvas_template,
                       96.0/xps->HWResolution[0], 0.0, 0.0,
                       96.0/xps->HWResolution[1], 0.0, 0.0);
        if (code < 0)
            return gs_rethrow_code(code);

        code = write_str_to_current_page(xps, buf);
        if (code < 0)
            return gs_rethrow_code(code);
    }

    if_debug4m('_', xps->memory,
               "page info: resx=%g resy=%g width=%d height=%d\n",
               xps->HWResolution[0], xps->HWResolution[1],
               (int)xps->MediaSize[0], (int)xps->MediaSize[1]);

    return code;
}

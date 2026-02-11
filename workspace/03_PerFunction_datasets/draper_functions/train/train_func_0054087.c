render_to_surface (ViewerCbInfo *info)
{
    int width, height;
    cairo_matrix_t matrix;
    cairo_surface_t *surface;
    cairo_t *cr;

    width = ceil ((double) info->dimensions.width * info->x_zoom);
    height = ceil ((double) info->dimensions.height * info->y_zoom);

    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);
    if (cairo_surface_status (surface) != CAIRO_STATUS_SUCCESS) {
        cairo_surface_destroy (surface);
        return NULL;
    }

    cr = cairo_create (surface);

    cairo_matrix_init_scale (&matrix, info->x_zoom, info->y_zoom);
    cairo_transform (cr, &matrix);

    if (!rsvg_handle_render_cairo_sub (info->handle, cr, info->id)) {
        cairo_destroy (cr);
        cairo_surface_destroy (surface);
        return NULL;
    }

    cairo_destroy (cr);

    if (cairo_surface_status (surface) != CAIRO_STATUS_SUCCESS) {
        g_printerr ("Error while rendering image: %d\n", cairo_surface_status (surface));
        cairo_surface_destroy (surface);
        return NULL;
    }

    return surface;
}

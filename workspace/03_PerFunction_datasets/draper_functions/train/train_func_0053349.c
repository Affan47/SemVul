initTestBuffer(unsigned width, unsigned height)
{
    cairo_surface_t* test_surface =
              cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);

    if (cairo_surface_status(test_surface) != CAIRO_STATUS_SUCCESS) {
        return false;
    }

    cairo_t* context = cairo_create(test_surface);
    if (cairo_status(context) == CAIRO_STATUS_NO_MEMORY) {
        return false;
    }

    cairo_surface_destroy(test_surface);
    set_context(context);

    return true;
}

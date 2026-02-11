cpl_image_wrap(cpl_size nx, cpl_size ny, cpl_type type,
                           void * pixels)
{
    cpl_image  * self;

    cpl_ensure(pixels != NULL, CPL_ERROR_NULL_INPUT, NULL);

    self = cpl_image_wrap_(nx, ny, type, pixels);

    if (self == NULL) (void)cpl_error_set_where_();

    return self;
}

cpl_frameset_dump(const cpl_frameset *self, FILE *stream)
{
    int i = 0;
    int n = 0;
    const cpl_frame *frame;

    if (self == NULL)
        return;

    if (stream == NULL)
        stream = stdout;

    n = cpl_frameset_get_size(self);

    if (n == 0)
        return;

    fprintf (stream, "+++ Frameset at address: %p\n", (const void *)self);

    cpl_frameset_iterator *it = cpl_frameset_iterator_new(self);

    while ((frame = cpl_frameset_iterator_get_const(it))) {

        fprintf(stream, "%3d  ", i++);
        cpl_frame_dump(frame, stream);

        cpl_errorstate status = cpl_errorstate_get();

        cpl_frameset_iterator_advance(it, 1);

        if (cpl_error_get_code() == CPL_ERROR_ACCESS_OUT_OF_RANGE)
        {
            cpl_errorstate_set(status);
        }

    }

    cpl_frameset_iterator_delete(it);

    return;
}

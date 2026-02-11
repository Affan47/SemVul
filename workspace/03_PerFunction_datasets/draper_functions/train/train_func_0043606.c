grain_maybe_realloc(guint *grain, guint w, guint h, guint *grainsize)
{
    if (w*h > *grainsize) {
        g_free(grain);
        *grainsize = w*h;
        grain = g_new(guint, *grainsize);
    }
    return grain;
}

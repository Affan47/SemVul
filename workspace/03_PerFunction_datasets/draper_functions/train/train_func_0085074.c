open_next_image(gboolean keep_next)
{
    GlivImage *next;
    GlivImage *future_image;

    if (currently_loading())
        return;

    if (keep_next) {
        forget_image(&previous_image);
    } else
        unload_images();


    future_image = next_image;
    next_image = NULL;

    next = load_in_direction(1);
    if (next == NULL)
        return;

    if (current_image != NULL) {
        previous_image = current_image;
        g_object_ref(previous_image);
    }

    next_image = future_image;

    render_next_image(next);
    g_object_unref(next);

    if (options->one_image == FALSE && next_image == NULL)
        next_image = load_in_direction(1);
}

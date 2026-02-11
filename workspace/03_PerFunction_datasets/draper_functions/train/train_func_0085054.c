load_in_direction(gint dir)
{
    GlivImage *im = NULL;
    GList *node;
    gint id;
    timestamp_t before_load = get_list_timestamp();

    if (get_list_length() == 2 && options->loop) {


        if (previous_image != NULL) {
            g_object_ref(previous_image);
            return previous_image;
        }

        if (next_image != NULL) {
            g_object_ref(next_image);
            return next_image;
        }
    }

    if (current_image == NULL) {

        node = NULL;
        id = 0;
    } else {
        node = current_image->node;
        id = get_image_number(current_image) + dir;
    }

    im = load_next_node(&node, dir);

    if (im == NULL && options->loop && get_list_length() > 1) {

        node = NULL;
        id = (dir == 1) ? 0 : (get_list_length() - 1);
        im = load_next_node(&node, dir);
    }

    if (im != NULL) {
        im->node = node;
        im->number = id;
    } else if (get_list_head() == NULL && current_image)

        current_image->node = NULL;

    if (before_load != get_list_timestamp())
        update_current_image_status(TRUE);

    return im;
}

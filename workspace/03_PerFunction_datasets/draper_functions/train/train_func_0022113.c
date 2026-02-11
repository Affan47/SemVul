load_second_image(void)
{
    if (next_image == NULL && options->one_image == FALSE)
        next_image = load_in_direction(1);

    if (options->start_show)
        start_slide_show();

    if (options->build_menus)
        do_later(G_PRIORITY_LOW, (GSourceDummyMarshal) rebuild_images_menus);
}

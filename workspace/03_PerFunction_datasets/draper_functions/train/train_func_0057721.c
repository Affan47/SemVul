display_check_structure(gx_device_display *ddev)
{
    if (ddev->callback == 0)
        return_error(gs_error_rangecheck);

    if (ddev->callback->size == sizeof(struct display_callback_v1_s)) {

        if (ddev->callback->version_major != DISPLAY_VERSION_MAJOR_V1)
            return_error(gs_error_rangecheck);


        if (ddev->callback->version_minor > DISPLAY_VERSION_MINOR_V1)
            return_error(gs_error_rangecheck);
    }
    else {

        if (ddev->callback->size != sizeof(display_callback))
            return_error(gs_error_rangecheck);

        if (ddev->callback->version_major != DISPLAY_VERSION_MAJOR)
            return_error(gs_error_rangecheck);


        if (ddev->callback->version_minor > DISPLAY_VERSION_MINOR)
            return_error(gs_error_rangecheck);
    }

    if ((ddev->callback->display_open == NULL) ||
        (ddev->callback->display_close == NULL) ||
        (ddev->callback->display_presize == NULL) ||
        (ddev->callback->display_size == NULL) ||
        (ddev->callback->display_sync == NULL) ||
        (ddev->callback->display_page == NULL))
        return_error(gs_error_rangecheck);


    return 0;
}

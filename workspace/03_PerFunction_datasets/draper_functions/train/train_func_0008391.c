cont_unreserve(gx_device_spot_analyzer *padev, gx_san_trap_contact *t)
{

    if (t->link != padev->cont_free)
        return_error(gs_error_unregistered);
    padev->cont_free = t;
    return 0;
}

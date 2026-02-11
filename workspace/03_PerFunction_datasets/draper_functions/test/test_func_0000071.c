os_banner_set_size(void *banner_handle, int siz, int siz_units, int is_advisory)
{
    osbanid_t banner = banner_handle;

    if (!banner || !banner->valid)
        return;

    glui32 gwinsize = siz;
    glui32 gwinmeth = 0;

    gwinmeth = banner->method &
        (winmethod_Above | winmethod_Below |
         winmethod_Left  | winmethod_Right);

    switch (siz_units)
    {
        case OS_BANNER_SIZE_PCT: gwinmeth |= winmethod_Proportional; break;
        case OS_BANNER_SIZE_ABS: gwinmeth |= winmethod_Fixed; break;
        default: gwinmeth |= winmethod_Fixed; break;
    }

    banner->method = gwinmeth;
    banner->size = gwinsize;

    os_banners_redraw();
}

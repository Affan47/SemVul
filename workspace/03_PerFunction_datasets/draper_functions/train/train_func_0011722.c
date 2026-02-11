gs_setnullcolor(gs_state * pgs)
{
    if (pgs->in_cachedevice)
        return_error(gs_error_undefined);
    gs_setgray(pgs, 0.0);
    color_set_null(gs_currentdevicecolor_inline(pgs));
    return 0;
}

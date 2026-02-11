doskip (void)
{

    if (framecnt >= currprefs.gfx_framerate)
        framecnt = 0;
    return framecnt > 0;
}

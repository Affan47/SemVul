WindowBoxType(screen_mode_t *mode, int w, int h)
{
    if (mode->width != w && mode->height != h)
    {
        return "Windowboxed";
    }
    else if (mode->width == w)
    {
        return "Letterboxed";
    }
    else if (mode->height == h)
    {
        return "Pillarboxed";
    }
    else
    {
        return "...";
    }
}

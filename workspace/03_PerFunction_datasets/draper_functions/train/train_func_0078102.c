color_new_exts(const GdkColor* gcolor, const char* exts)
{
    color_t* color;

    color = color_new(gcolor->red, gcolor->green, gcolor->blue, COLOR_EXTENSION);
    if (exts)
    {
        char* temp = g_strdup(exts);
        char* cur = temp;
        char* pos;

        while ((pos = strchr(cur, ' ')) != NULL)
        {
            *pos = 0;
            color_add_ext(color, cur);
            cur = pos+1;
        }
        color_add_ext(color, cur);
    }
    return color;
}

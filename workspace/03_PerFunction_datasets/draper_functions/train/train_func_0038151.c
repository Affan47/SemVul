emit_rect_image(int width, int height, const char *label, int hspace)
{
    if (width < 3)
        width = 3;
    if (height < 3)
        height = 3;
    printf
    (
        "<img src=\"%s/?rect+width=%d+height=%d",
        http_script_name(),
        width,
        height
    );
    if (label && *label)
    {
        printf("+label=");
        html_escape_charstar(label);
    }
    printf("\" width=%d height=%d", width, height);
    if (hspace >= 0)
    {
#ifndef USE_STYLES
        printf(" hspace=%d", hspace);
#else
        printf(" style=\"left:%d;right:%d;\"", hspace, hspace);
#endif
    }
    printf(">");
}

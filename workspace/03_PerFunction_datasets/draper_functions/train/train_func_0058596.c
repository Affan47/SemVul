xdg_mime_media_type_equal(const char *mime_a,
                          const char *mime_b)
{
    char *sep;

    xdg_mime_init();

    sep = const_cast<char*>(strchr(mime_a, '/'));

    if (sep && strncmp(mime_a, mime_b, sep - mime_a + 1) == 0)
        return 1;

    return 0;
}

iptux_erase_filename_suffix(const char *filename)
{
        const char *ptr;
        char *file;

        ptr = strrchr(filename, '.');
        if (ptr && ptr != filename)
                file = g_strndup(filename, ptr - filename);
        else
                file = g_strdup(filename);

        return file;
}

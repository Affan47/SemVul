ff_pretty_file(ft_log_event & event)
{
    const char * file = event.file;
    if (!strncmp(file, "../", 3))
        file += 3;
    if (!strncmp(file, "src/", 3))
        file += 4;
    ft_size file_len = strlen(file);


    const char * dot = (const char *) memrchr(file, '.', file_len);
    if (dot != NULL)
        file_len = dot - file;


    if (file_len >= 2 && !strncmp(file + file_len - 2, ".t", 2)) {
        file_len -= 2;
        event.file_suffix = "<T>";
    }
    event.file = file;

    event.file_len = file_len;
    if (event.file_len < 0 || file_len != (ft_size) event.file_len)
        event.file_len = 255;
}

explain_buffer_fildes_to_path(explain_string_buffer_t *sb, int fildes)
{
    char            path[PATH_MAX + 1];

    if (explain_fileinfo_self_fd_n(fildes, path, sizeof(path)))
    {
        explain_string_buffer_putc(sb, ' ');
        explain_string_buffer_puts_quoted(sb, path);
    }
}

command_interpreter_broken(explain_string_buffer_t *sb, const char *pathname)
{
    char            block[512];
    int             fd;
    ssize_t         n;
    char            *end;
    char            *interpreter_pathname;
    explain_final_t final_component;
    char            *bp;

    fd = open(pathname, O_RDONLY);
    if (fd < 0)
        return -1;
    n = read(fd, block, sizeof(block) - 1);
    close(fd);
    if (n < 4)
        return -1;
    end = block + n;
    if (block[0] != '#')
        return -1;
    if (block[1] != '!')
        return -1;
    bp = block + 2;
    while (bp < end && (*bp == ' ' || *bp == '\t'))
        ++bp;
    if (bp >= end)
        return -1;
    interpreter_pathname = bp;
    ++bp;
    while (bp < end && !isspace(*bp))
        ++bp;
    *bp = '\0';

    explain_final_init(&final_component);
    final_component.want_to_execute = 1;
    final_component.follow_interpreter = 0;
    return
        explain_buffer_errno_path_resolution
        (
            sb,
            EACCES,
            interpreter_pathname,
            "#!",
            &final_component
        );
}

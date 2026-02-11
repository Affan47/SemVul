http_check_header_line(struct httplocalfile *lf)
{
    int res;
    char *line;

    res = http_get_line(lf, &line);
    if(res < 0)
        return res;

    if(line[0] == '\0')
        res = 0;
    else {
        http_process_header_line(lf, line);
        res = 1;
    }
    av_free(line);

    return res;
}

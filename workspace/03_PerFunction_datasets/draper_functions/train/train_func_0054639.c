do_com_data(char *str)
{
    char           *in;
    if (strlen(str) < 2) {
        printf_error("no parameter '%s'", gl->pc->str);
        return 1;
    }
    in = str;
    gl->lastchar = ' ';
    gl->line_cnt = 1;
    gl->line_path = gl->pc->path;
    gl->root = read_aisc(&in);
    if (!gl->root) {
        printf_error("occurred in following script-part: '%s'", gl->pc->str);
        return 1;
    }
    return 0;
}

match_inline(char *arg, struct session *ses)
{
    pvars_t vars;
    char left[BUFFER_SIZE], line[BUFFER_SIZE];

    arg=get_arg(arg, left, 0, ses);
    arg=get_arg(arg, line, 1, ses);

    if (!*left)
    {
        tintin_eprintf(ses,"#ERROR: valid syntax is: (#match <pattern> <line>)");
        return 0;
    }

    return check_one_action(line, left, &vars, 0, ses);
}

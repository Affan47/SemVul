dosubstitutes_command(char *arg,struct session *ses)
{
    char left[BUFFER_SIZE], right[BUFFER_SIZE];

    arg = get_arg(arg, left, 0, ses);
    arg = get_arg(arg, right, 1, ses);
    if (!*left || !*right)
        tintin_eprintf(ses,"#Syntax: #dosubstitutes <var> <text>");
    else
    {
        do_all_sub(right, ses);
        set_variable(left,right,ses);
    }
}

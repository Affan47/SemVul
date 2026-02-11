changeto_command(char *arg, struct session *ses)
{
    char left[BUFFER_SIZE], temp[BUFFER_SIZE];

    if (!_)
    {
        tintin_eprintf(ses, "#ERROR: #change is allowed only inside an action/promptaction");
        return;
    }

    get_arg_in_braces(arg, left, 1);
    substitute_vars(left, temp);
    substitute_myvars(temp, left, ses);
    strcpy(_, left);
}

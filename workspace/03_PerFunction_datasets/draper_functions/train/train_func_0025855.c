get_history_arg(xp, idx)
    expand_T	*xp UNUSED;
    int		idx;
{
    static char_u compl[2] = { NUL, NUL };
    char *short_names = ":=@>?/";
    int short_names_count = (int)STRLEN(short_names);
    int history_name_count = sizeof(history_names) / sizeof(char *) - 1;

    if (idx < short_names_count)
    {
	compl[0] = (char_u)short_names[idx];
	return compl;
    }
    if (idx < short_names_count + history_name_count)
	return (char_u *)history_names[idx - short_names_count];
    if (idx == short_names_count + history_name_count)
	return (char_u *)"all";
    return NULL;
}

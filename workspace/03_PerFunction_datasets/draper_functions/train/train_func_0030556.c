extract_change_number(string_ty **project_name_p, long *change_number_p)
{
    string_ty       *project_name;
    char            *end;
    long            change_number;

    project_name = *project_name_p;
    const char *cp =
        (const char *)
        memmem(project_name->str_text, project_name->str_length, ".C", 2);
    if (!cp)
    {
	cp =
            (const char *)
            memmem(project_name->str_text, project_name->str_length, ".c", 2);
    }
    if (!cp)
	return false;
    change_number = strtol(cp + 2, &end, 10);
    if (end == cp + 2 || *end)
	return false;


    *change_number_p = change_number;
    *project_name_p =
	str_n_from_c(project_name->str_text, cp - project_name->str_text);
    return true;
}

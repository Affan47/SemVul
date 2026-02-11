check(change::pointer cp, fstate_src_ty *src)
{


    if
    (
        attributes_list_find_boolean
        (
            src->attribute,
            "aede-policy-tabs-allowed"
        )
    )
        return true;


    nstring t(src->file_name);
    if (t.basename().downcase().starts_with("makefile"))
        return true;

    string_ty *path = change_file_path(cp, src);
    assert(path);
    if (!path)
        return true;

    os_become_orig();
    bool ok = true;
    input ip = input_file_text_open(path);
    for (;;)
    {
        int c = ip->getch();
        if (c < 0)
            break;
        if (c == 0)
        {

            break;
        }
        if (c == '\t')
        {
            ok = false;
            break;
        }
    }
    ip.close();
    os_become_undo();
    if (!ok)
    {
        sub_context_ty sc;
        sc.var_set_string("File_Name", src->file_name);
        change_error(cp, &sc, i18n("$filename: contains tab characters"));
    }
    return ok;
}

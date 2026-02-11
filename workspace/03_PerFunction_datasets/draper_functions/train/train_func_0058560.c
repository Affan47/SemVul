copy_tree_callback(void *arg, dir_walk_message_ty message, string_ty *path,
    const struct stat *st)
{
    string_ty       *s1;
    string_ty       *s1short;
    string_ty       *s2;
    change::pointer cp;
    int             uid;
    string_ty       *contents;
    int             exists;

    trace(("copy_tree_callback(message = %d, path = %08lX, st = %08lX)\n{\n",
        message, (long)path, (long)st));
    os_interrupt_cope();
    cp = (change::pointer )arg;
    assert(cp);
    trace_string(path->str_text);
    s1 = os_below_dir(cp->pp->baseline_path_get(true), path);
    assert(s1);
    trace_string(s1->str_text);
    if (!s1->str_length)
        s2 = str_copy(change_integration_directory_get(cp, 1));
    else
        s2 = os_path_join(change_integration_directory_get(cp, 1), s1);
    trace_string(s2->str_text);
    switch (message)
    {
    case dir_walk_dir_before:
        assert(!os_exists(s2));
        os_mkdir(s2, 02755);
        break;

    case dir_walk_file:


        os_become_query(&uid, (int *)0, (int *)0);
        if
        (
            (unsigned int)st->st_uid != (unsigned int)uid
        ||
            (st->st_mode & 07000) != 0
        )
        {
            project_become_undo(cp->pp);
            exists = !!project_file_find(cp->pp, s1, view_path_extreme);
            project_become(cp->pp);
            if (!exists)
                break;
        }


        s1short = remove_comma_d_if_present(s1);
        trace_string(s1short->str_text);


        if (change_file_find(cp, s1short, view_path_first))
        {
            str_free(s1short);
            break;
        }


        project_become_undo(cp->pp);
        {
            bool remove_the_file =
                (
                    !project_file_find(cp->pp, s1short, view_path_extreme)
                &&
                    !ends_with_comma_d(s1)
                &&
                    isa_suppressed_filename(cp, s1short)
                );
            project_become(cp->pp);
            str_free(s1short);
            if (remove_the_file)
                break;
        }


        copy_whole_file(path, s2, 1);
        project_become_undo(cp->pp);
        exists = !!project_file_find(cp->pp, s1, view_path_extreme);
        project_become(cp->pp);
        chmod_common(s2, st, !exists, cp);
        break;

    case dir_walk_dir_after:
        break;

    case dir_walk_symlink:
        contents = os_readlink(path);
        os_symlink(contents, s2);
        str_free(contents);
        break;

    case dir_walk_special:


        break;
    }
    str_free(s2);
    str_free(s1);
    trace(("}\n"));
}

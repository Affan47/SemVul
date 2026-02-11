run_make_transparent_undo_command(string_list_ty *wlp,
    const user_ty::pointer &up)
{
    trace(("change::run_make_transparent_undo_command(this = %08lX)\n{\n",
	(long)this));

    assert(!lock_active());
    assert(reference_count >= 1);
    pconf_ty *pcp = change_pconf_get(this, 0);
    string_ty *the_command = pcp->make_transparent_undo_command;
    if (!the_command)
	the_command = pcp->change_file_undo_command;
    if (!the_command)
	the_command = pcp->change_file_command;
    if (!the_command || !the_command->str_length)
    {
        trace(("}\n"));
        return;
    }

    sub_context_ty sc;
    string_ty *the_files = wlp->unsplit();
    sc.var_set_string("File_List", the_files);
    sc.var_optional("File_List");
    str_free(the_files);
    the_command = sc.substitute(this, the_command);

    string_ty *dd = change_development_directory_get(this, 0);
    change_env_set(this, 0);
    user_ty::become scoped(up);
    os_execute(the_command, OS_EXEC_FLAG_NO_INPUT | OS_EXEC_FLAG_ERROK, dd);
    str_free(the_command);
    trace(("}\n"));
}

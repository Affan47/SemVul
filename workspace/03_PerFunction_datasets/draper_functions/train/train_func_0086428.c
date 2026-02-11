run_review_pass_undo_notify_command()
{
    trace(("change::run_review_pass_undo_notify_command(this = %08lX)\n{\n",
	(long)this));


    assert(!lock_active());
    assert(reference_count >= 1);
    string_ty *notify = project_review_pass_undo_notify_command_get(pp);
    if (!notify)
	notify = project_develop_end_undo_notify_command_get(pp);
    if (!notify || !notify->str_length)
    {
        trace(("}\n"));
	return;
    }


    sub_context_ty sc;
    string_ty *the_command = sc.substitute(this, notify);


    string_ty *dd = change_development_directory_get(this, 0);
    change_env_set(this, 0);
    change_become(this);
    os_execute(the_command, OS_EXEC_FLAG_NO_INPUT + OS_EXEC_FLAG_ERROK, dd);
    str_free(the_command);
    change_become_undo(this);
    trace(("}\n"));
}

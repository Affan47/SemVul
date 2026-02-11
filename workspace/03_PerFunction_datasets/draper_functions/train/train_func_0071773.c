os_edit(const nstring &filename, edit_ty et)
{


    os_become_must_not_be_active();
    nstring editor;
    if (et == edit_background)
    {
	editor = user_ty::create()->editor_command();
    }
    else
    {
	editor = user_ty::create()->visual_command();
	const char *cp = strrchr(editor.c_str(), '/');
	if (!cp)
            cp = editor.c_str();
	if (0 == strcmp(cp, "ed"))
            et = edit_background;
    }


    if (et != edit_background && os_background())
    {
	sub_context_ty sc;
	sc.var_set_charstar("Name", arglex_token_name(arglex_token_edit));
	sc.fatal_intl(i18n("may not use $name in the background"));

    }


    nstring cmd = nstring::format("%s %s", editor.c_str(), filename.c_str());
    os_become_orig();
    nstring cwd(os_curdir());
    assert(cwd);
    os_execute(cmd, OS_EXEC_FLAG_INPUT | OS_EXEC_FLAG_ERROK, cwd);
    os_become_undo();
}

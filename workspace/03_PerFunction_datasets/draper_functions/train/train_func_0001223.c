panel_act_MKDIR(this, other)
    panel_t *this, *other;
{
    size_t len;
    char *input = NULL, *tmp_input;

    if (!il_read_line("New directory name: ", &input, NULL, mkdir_history))
	return;

    if (input[0] == '\0')
    {
	xfree(input);
	return;
    }

    tmp_input = tilde_expand(input);
    xfree(input);
    input = tmp_input;


    len = strlen(input);
    input = realloc(input, len + 1 + 1);
    input[len] = '/';
    input[len + 1] = '\0';


    if (panel_mkdirs(input, S_IFDIR | S_IRWXU | S_IRWXG | S_IRWXO) == -1)
    {
	panel_2s_message("%s: Permission denied.", input,
			 (char *)NULL,
			 IL_FREEZED | IL_BEEP | IL_SAVE | IL_ERROR);
	xfree(input);
	return;
    }

    if (!panel_read_directory(this, this->path, ON))
	panel_recover(this);
    else
    {


	this->current_entry = panel_find_index(this, input);
	this->first_on_screen = panel_get_centered_fos(this);
	panel_update_entries(this);
	panel_update_info(this);
	panel_update_size(this);
    }

    if (strcmp(this->path, other->path) == 0)
    {
	char *old_entry = xstrdup(other->dir_entry[other->current_entry].name);

	if (!panel_read_directory(other, other->path, ON))
	    panel_recover(other);
	else
	{
	    other->current_entry = panel_find_index(other, old_entry);
	    other->first_on_screen = panel_get_centered_fos(other);
	    panel_update_entries(other);
	    panel_update_info(other);
	}

	xfree(old_entry);
    }

    panel_update_size(other);
    xfree(input);
}

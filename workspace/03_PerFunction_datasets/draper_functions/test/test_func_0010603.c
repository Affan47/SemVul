panel_act_ENTER(this, other)
    panel_t *this, *other;
{
    int back;
    char *old_path, *cmd, *old_entry_name;
    char *name = this->dir_entry[this->current_entry].name;

    switch (this->dir_entry[this->current_entry].type)
    {
	case DIR_ENTRY:
	    if (strcmp(name, "..") == 0 && strcmp(this->path, "/") == 0)
		break;

	    back = (strcmp(name, "..") == 0) ? 1 : 0;

	    old_path = xmalloc(this->pathlen + 1);
	    strcpy(old_path, this->path);

	    if (!panel_read_directory(this, name, ON))
	    {
		if (back)
		{
		    panel_recover(this);
		    panel_update(this);
		}
		else
		    panel_2s_message("%s/: Permission denied.",
				     name, (char *)NULL,
				     IL_FREEZED | IL_BEEP |
				     IL_SAVE    | IL_ERROR);
		break;
	    }

	    if (back)
	    {
		int index;

		old_entry_name = strrchr(old_path, '/');
		assert(old_entry_name);
		index = panel_find_index(this, ++old_entry_name);
		panel_set_current_entry(this, index);
	    }
	    else
		panel_set_current_entry(this, 0);

	    xfree(old_path);

	    panel_update(this);

	    if (strcmp(this->path, other->path) == 0)
	    {
		panel_action(other, act_REGET, this, (void *)-1, 1);
		panel_update(other);
	    }
	    else
		panel_update_size(other);

	    break;

	case FILE_ENTRY:
	    if (this->dir_entry[this->current_entry].executable)
	    {
		cmd = xmalloc(32 + strlen(name) + 1);
		sprintf(cmd, "./\"%s\"", name);
		start(cmd, 0);
		wait_msg = 1;
		xfree(cmd);

		tty_touch();
		tty_get_screen(screen);
		panel_no_optimizations(this);
		panel_no_optimizations(other);
		il_insert_text(name);
		tty_update_title(this->path);
		return 1;
	    }

	    break;
	}

    return 0;
}

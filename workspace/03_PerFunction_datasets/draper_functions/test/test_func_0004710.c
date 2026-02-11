panel_act_REGET(this, aux_info)
    panel_t *this;
    void *aux_info;
{
    char *old_entry;
    int flag, verify;

    if (this->dir_entry && this->dir_entry[this->current_entry].name)
    {
	old_entry = xstrdup(this->dir_entry[this->current_entry].name);
	flag = 1;
    }
    else
	old_entry = "", flag = 0;

    verify = aux_info == (void *)-1;

    if (panel_read_directory(this, this->path, verify))
    {
	if (verify)
	    panel_set_current_entry(this, panel_find_index(this, old_entry));
	else
	    panel_set_current_entry(this, 0);
    }
    else
	panel_recover(this);

    if (flag)
	xfree(old_entry);
}

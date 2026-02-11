do_left(void)
{
    size_t pww_save = openfile->placewewant;

    if (openfile->current_x > 0)
	openfile->current_x = move_mbleft(openfile->current->data,
		openfile->current_x);
    else if (openfile->current != openfile->fileage) {
	do_up_void();
	openfile->current_x = strlen(openfile->current->data);
    }

    openfile->placewewant = xplustabs();

    if (need_horizontal_update(pww_save))
	update_line(openfile->current, openfile->current_x);
}

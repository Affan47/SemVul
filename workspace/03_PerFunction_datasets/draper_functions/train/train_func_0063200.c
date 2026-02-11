do_para_end(bool allow_update)
{
    filestruct *const current_save = openfile->current;
    const size_t pww_save = openfile->placewewant;

    while (openfile->current != openfile->filebot &&
	!inpar(openfile->current))
	openfile->current = openfile->current->next;

    while (openfile->current != openfile->filebot &&
	inpar(openfile->current->next) &&
	!begpar(openfile->current->next)) {
	openfile->current = openfile->current->next;
	openfile->current_y++;
    }

    if (openfile->current != openfile->filebot) {
	openfile->current = openfile->current->next;
	openfile->current_x = 0;
	openfile->placewewant = 0;
    } else {
	openfile->current_x = strlen(openfile->current->data);
	openfile->placewewant = xplustabs();
    }

    if (allow_update)
	edit_redraw(current_save, pww_save);
}

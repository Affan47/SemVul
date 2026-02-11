do_home(void)
{
    size_t pww_save = openfile->placewewant;

#ifndef NANO_TINY
    if (ISSET(SMART_HOME)) {
	size_t current_x_save = openfile->current_x;

	openfile->current_x = indent_length(openfile->current->data);

	if (openfile->current_x == current_x_save ||
		openfile->current->data[openfile->current_x] == '\0')
	    openfile->current_x = 0;

	openfile->placewewant = xplustabs();
    } else {
#endif
	openfile->current_x = 0;
	openfile->placewewant = 0;
#ifndef NANO_TINY
    }
#endif

    if (need_horizontal_update(pww_save))
	update_line(openfile->current, openfile->current_x);
}

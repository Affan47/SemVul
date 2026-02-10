copy_from_filestruct(filestruct *file_top, filestruct *file_bot)
{
    filestruct *top_save;
    size_t current_x_save = openfile->current_x;
    bool edittop_inside;
#ifndef NANO_TINY
    bool right_side_up = FALSE, single_line = FALSE;
#endif

    assert(file_top != NULL && file_bot != NULL);

#ifndef NANO_TINY


    if (openfile->mark_set) {
	filestruct *top, *bot;
	size_t top_x, bot_x;

	mark_order((const filestruct **)&top, &top_x,
		(const filestruct **)&bot, &bot_x, &right_side_up);

	single_line = (top == bot);
    }
#endif


    filepart = partition_filestruct(openfile->current,
	openfile->current_x, openfile->current, openfile->current_x);
    edittop_inside = (openfile->edittop == openfile->fileage);


    openfile->fileage = copy_filestruct(file_top);
    openfile->filebot = openfile->fileage;
    while (openfile->filebot->next != NULL)
	openfile->filebot = openfile->filebot->next;


    openfile->current = openfile->filebot;
    openfile->current_x = strlen(openfile->filebot->data);
    if (openfile->fileage == openfile->filebot) {
#ifndef NANO_TINY
	if (openfile->mark_set) {
	    openfile->mark_begin = openfile->current;
	    if (!right_side_up)
		openfile->mark_begin_x += openfile->current_x;
	}
#endif
	openfile->current_x += current_x_save;
    }
#ifndef NANO_TINY
    else if (openfile->mark_set) {
	if (!right_side_up) {
	    if (single_line) {
		openfile->mark_begin = openfile->current;
		openfile->mark_begin_x -= current_x_save;
	    } else
		openfile->mark_begin_x -= openfile->current_x;
	}
    }
#endif


    openfile->totsize += get_totsize(openfile->fileage,
	openfile->filebot);


    openfile->current_y += openfile->filebot->lineno - 1;

    top_save = openfile->fileage;


    if (edittop_inside)
	openfile->edittop = openfile->fileage;


    unpartition_filestruct(&filepart);


    renumber(top_save);


    if (!ISSET(NO_NEWLINES) && openfile->filebot->data[0] != '\0')
	new_magicline();
}

redo()
{
	gTextAreaAction *action;
	GtkTextIter start, stop;

	if (!_redo_stack)
		return;

	begin();
	_undo_in_progress = true;

	action = _redo_stack;
	_redo_stack = _redo_stack->next;

	action->prev = NULL;
	action->next = _undo_stack;
	if (_undo_stack)
		_undo_stack->prev = action;
	_undo_stack = action;

	if (action->type == ACTION_INSERT)
	{
		gtk_text_buffer_get_iter_at_offset(_buffer, &start, action->start);
		gtk_text_buffer_insert(_buffer, &start, action->text->str, action->text->len);
		gtk_text_buffer_get_iter_at_offset(_buffer, &start, action->start + action->length);
		gtk_text_buffer_place_cursor(_buffer, &start);
	}
	else if (action->type == ACTION_DELETE)
	{
		gtk_text_buffer_get_iter_at_offset(_buffer, &start, action->start);
		gtk_text_buffer_get_iter_at_offset(_buffer, &stop, action->end);
		gtk_text_buffer_delete(_buffer, &start, &stop);
		gtk_text_buffer_place_cursor(_buffer, &start);
	}

	end();
	ensureVisible();
	_undo_in_progress = false;
}

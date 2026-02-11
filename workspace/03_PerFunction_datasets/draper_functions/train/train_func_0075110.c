il_delete_horizontal_space()
{
    if (il->buffer[il->point] == ' ')
    {
	while (il->buffer[il->point] == ' ')
	    il_delete_char();

	while (il->dynamic_length && il->buffer[il->point - 1] == ' ')
	    il_backward_delete_char();

	il->last_operation = IL_DELETE_HORIZONTAL_SPACE;
    }
}

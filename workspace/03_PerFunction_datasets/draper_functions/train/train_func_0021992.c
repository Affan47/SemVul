il_backward_delete_char()
{
    if (il->point > il->static_length)
    {
	memcpy(il->buffer + il->point - 1,
	       il->buffer + il->point,
	       il->length - il->point + 1);

	il->point--;
	il->length--;
	il->dynamic_length--;

	if (il->length % 16 == 0)
	    IL_RESIZE(il->length + 1);

	il->last_operation = IL_BACKWARD_DELETE_CHAR;
    }
}

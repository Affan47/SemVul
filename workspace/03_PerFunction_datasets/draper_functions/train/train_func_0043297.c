ast_audiohook_volume_get(struct ast_channel *chan, enum ast_audiohook_direction direction)
{
	struct audiohook_volume *audiohook_volume = NULL;
	int adjustment = 0;


	if (!(audiohook_volume = audiohook_volume_get(chan, 0))) {
		return 0;
	}


	if (direction == AST_AUDIOHOOK_DIRECTION_READ) {
		adjustment = audiohook_volume->read_adjustment;
	} else if (direction == AST_AUDIOHOOK_DIRECTION_WRITE) {
		adjustment = audiohook_volume->write_adjustment;
	}

	return adjustment;
}

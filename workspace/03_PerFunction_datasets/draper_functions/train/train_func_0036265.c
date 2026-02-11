ast_audiohook_volume_adjust(struct ast_channel *chan, enum ast_audiohook_direction direction, int volume)
{
	struct audiohook_volume *audiohook_volume = NULL;


	if (!(audiohook_volume = audiohook_volume_get(chan, 1))) {
		return -1;
	}


	if (direction == AST_AUDIOHOOK_DIRECTION_READ || direction == AST_AUDIOHOOK_DIRECTION_BOTH) {
		audiohook_volume->read_adjustment += volume;
	}
	if (direction == AST_AUDIOHOOK_DIRECTION_WRITE || direction == AST_AUDIOHOOK_DIRECTION_BOTH) {
		audiohook_volume->write_adjustment += volume;
	}

	return 0;
}

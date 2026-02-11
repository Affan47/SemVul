ast_channel_stop_silence_generator(struct ast_channel *chan, struct ast_silence_generator *state)
{
	if (!state)
		return;

	if (internal_deactivate_generator(chan, &silence_generator)) {
		ast_debug(1, "Stopped silence generator on '%s'\n", ast_channel_name(chan));
		if (ast_set_write_format(chan, &state->old_write_format) < 0)
			ast_log(LOG_ERROR, "Could not return write format to its original state\n");
	}
	ast_free(state);
}

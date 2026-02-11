ast_dial_option_enable(struct ast_dial *dial, int num, enum ast_dial_option option, void *data)
{
	struct ast_dial_channel *channel = NULL;


	if (!dial || AST_LIST_EMPTY(&dial->channels))
		return -1;

	if (!(channel = find_dial_channel(dial, num)))
		return -1;


	if (channel->options[option])
		return -1;


	if (option_types[option].enable)
		channel->options[option] = option_types[option].enable(data);
	else
		channel->options[option] = (void*)1;

	return 0;
}

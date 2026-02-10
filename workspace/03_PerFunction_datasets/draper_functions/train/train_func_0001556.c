get_messages(struct chat_history_data* data, size_t num, struct cbuffer* outbuf)
{
	struct linked_list* messages = data->chat_history;
	char* message;
	int skiplines = 0;
	size_t lines = 0;
	size_t total = list_size(messages);

	if (total == 0)
		return 0;

	if (num <= 0 || num > total)
		num = total;

	if (num != total)
		skiplines = total - num;

	cbuf_append(outbuf, "\n");
	LIST_FOREACH(char*, message, messages,
	{
		if (--skiplines < 0)
		{
			cbuf_append(outbuf, message);
			lines++;
		}
	});
	cbuf_append(outbuf, "\n");
	return lines;
}

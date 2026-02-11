il_history_add_entry(history, text)
    xstack_t *history;
    char *text;
{
    char *history_text;


    if (xstack_preview(history, &history_text, 1) &&
	strcmp(history_text, text) == 0)
	return;

    history_text = xstrdup(text);
    xstack_push(history, &history_text);
}

cmd_ts(const char *data)
{
	GSList *tmp;

	g_return_if_fail(data != NULL);

	for (tmp = channels; tmp != NULL; tmp = tmp->next) {
		CHANNEL_REC *rec = tmp->data;

		printformat(NULL, NULL, MSGLEVEL_CLIENTNOTICE, IRCTXT_TOPIC,
			    rec->visible_name,
			    rec->topic == NULL ? "" : rec->topic);
	}
}

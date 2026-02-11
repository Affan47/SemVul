Term_key_push(int k)
{
	ui_event_data ke;

	if (!k) return (-1);

	ke.type = EVT_KBRD;
	ke.index = 0;
	ke.key = k;

	return Term_event_push(&ke);
}

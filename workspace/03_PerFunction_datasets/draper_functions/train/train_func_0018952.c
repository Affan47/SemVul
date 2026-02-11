tabnick_flush()
{
	int i;

	for (i = 0; i < send_nicks_count; i++) {
		xfree(send_nicks[i]);
		send_nicks[i] = NULL;
	}

	send_nicks_count = 0;
	send_nicks_index = 0;
}

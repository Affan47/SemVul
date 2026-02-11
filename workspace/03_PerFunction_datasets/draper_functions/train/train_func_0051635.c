analog_handle_notify_message(struct ast_channel *chan, struct analog_pvt *p, int cid_flags, int neon_mwievent)
{
	if (analog_callbacks.handle_notify_message) {
		analog_callbacks.handle_notify_message(chan, p->chan_pvt, cid_flags, neon_mwievent);
		return 0;
	}
	return -1;
}

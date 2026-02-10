safelist_sendq_exceeded(struct Client *client_p)
{
	if (rb_linebuf_len(&client_p->localClient->buf_sendq) > (get_sendq(client_p) / 2))
		return YES;
	else
		return NO;
}

stats_l_client(struct Client *source_p, struct Client *target_p, char statchar)
{
	if(IsAnyServer(target_p))
	{
		sendto_one_numeric(source_p, RPL_STATSLINKINFO, Lformat,
				   target_p->name,
				   rb_linebuf_len(&target_p->localClient->buf_sendq),
				   target_p->localClient->sendM,
				   target_p->localClient->sendB / 1024,
				   target_p->localClient->receiveM,
				   target_p->localClient->receiveB / 1024,
				   (long)rb_current_time() - target_p->localClient->firsttime,
				   (long)(rb_current_time() > target_p->localClient->lasttime) ?
				   (long)(rb_current_time() - target_p->localClient->lasttime) : 0,
				   IsOper(source_p) ? show_capabilities(target_p) : "-");
	}

	else if(!show_ip(source_p, target_p))
	{
		sendto_one_numeric(source_p, RPL_STATSLINKINFO, Lformat,
				   get_client_name(target_p, MASK_IP),
				   rb_linebuf_len(&target_p->localClient->buf_sendq),
				   target_p->localClient->sendM,
				   target_p->localClient->sendB / 1024,
				   target_p->localClient->receiveM,
				   target_p->localClient->receiveB / 1024,
				   (long)(rb_current_time() - target_p->localClient->firsttime),
				   (long)(rb_current_time() > target_p->localClient->lasttime) ?
				   (long)(rb_current_time() - target_p->localClient->lasttime) : 0,
				   "-");
	}

	else
	{
		sendto_one_numeric(source_p, RPL_STATSLINKINFO, Lformat,
				   IsUpper(statchar) ?
				   get_client_name(target_p, SHOW_IP) :
				   get_client_name(target_p, HIDE_IP),
				   rb_linebuf_len(&target_p->localClient->buf_sendq),
				   target_p->localClient->sendM,
				   target_p->localClient->sendB / 1024,
				   target_p->localClient->receiveM,
				   target_p->localClient->receiveB / 1024,
				   (long)rb_current_time() - target_p->localClient->firsttime,
				   (long)(rb_current_time() > target_p->localClient->lasttime) ?
				   (long)(rb_current_time() - target_p->localClient->lasttime) : 0,
				   "-");
	}
}

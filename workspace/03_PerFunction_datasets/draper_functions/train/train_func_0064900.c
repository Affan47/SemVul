stats_l_client(struct Client *source_p, struct Client *target_p,
		char statchar)
{
	if(IsAnyServer(target_p))
	{
		sendto_one_numeric(source_p, RPL_STATSLINKINFO, Lformat,
				target_p->name,
				(int) rb_linebuf_len(&target_p->localClient->buf_sendq),
				(int) target_p->localClient->sendM,
				(int) target_p->localClient->sendK,
				(int) target_p->localClient->receiveM,
				(int) target_p->localClient->receiveK,
				rb_current_time() - target_p->localClient->firsttime,
				(rb_current_time() > target_p->localClient->lasttime) ?
				 (rb_current_time() - target_p->localClient->lasttime) : 0,
				IsOper(source_p) ? show_capabilities(target_p) : "-");
	}

	else
	{
		sendto_one_numeric(source_p, RPL_STATSLINKINFO, Lformat,
				   show_ip(source_p, target_p) ?
				    (IsUpper(statchar) ?
				     get_client_name(target_p, SHOW_IP) :
				     get_client_name(target_p, HIDE_IP)) :
				    get_client_name(target_p, MASK_IP),
				    (int) rb_linebuf_len(&target_p->localClient->buf_sendq),
				    (int) target_p->localClient->sendM,
				    (int) target_p->localClient->sendK,
				    (int) target_p->localClient->receiveM,
				    (int) target_p->localClient->receiveK,
				    rb_current_time() - target_p->localClient->firsttime,
				    (rb_current_time() > target_p->localClient->lasttime) ?
				     (rb_current_time() - target_p->localClient->lasttime) : 0,
				    "-");
	}
}

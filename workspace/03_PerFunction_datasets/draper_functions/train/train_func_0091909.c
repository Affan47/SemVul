sendto_match_butone(struct Client *one, struct Client *source_p,
		    const char *mask, int what, const char *pattern, ...)
{
	static char buf[BUFSIZE];
	va_list args;
	struct Client *target_p;
	rb_dlink_node *ptr;
	rb_dlink_node *next_ptr;
	buf_head_t rb_linebuf_local;
	buf_head_t rb_linebuf_id;

	rb_linebuf_newbuf(&rb_linebuf_local);
	rb_linebuf_newbuf(&rb_linebuf_id);

	va_start(args, pattern);
	rb_vsnprintf(buf, sizeof(buf), pattern, args);
	va_end(args);

	if(IsServer(source_p))
		rb_linebuf_putmsg(&rb_linebuf_local, NULL, NULL,
			       ":%s %s", source_p->name, buf);
	else
		rb_linebuf_putmsg(&rb_linebuf_local, NULL, NULL,
			       ":%s!%s@%s %s",
			       source_p->name, source_p->username,
			       source_p->host, buf);

	rb_linebuf_putmsg(&rb_linebuf_id, NULL, NULL, ":%s %s", use_id(source_p), buf);

	if(what == MATCH_HOST)
	{
		RB_DLINK_FOREACH_SAFE(ptr, next_ptr, lclient_list.head)
		{
			target_p = ptr->data;

			if(match(mask, target_p->host))
				_send_linebuf(target_p, &rb_linebuf_local);
		}
	}

	else if(match(mask, me.name))
	{
		RB_DLINK_FOREACH_SAFE(ptr, next_ptr, lclient_list.head)
		{
			target_p = ptr->data;
			_send_linebuf(target_p, &rb_linebuf_local);
		}
	}

	RB_DLINK_FOREACH(ptr, serv_list.head)
	{
		target_p = ptr->data;

		if(target_p == one)
			continue;

		send_linebuf_remote(target_p, source_p, &rb_linebuf_id);
	}

	rb_linebuf_donebuf(&rb_linebuf_local);
	rb_linebuf_donebuf(&rb_linebuf_id);
}

ssl_process_cmd_recv(ssl_ctl_t * ctl)
{
	static const char *cannot_setup_ssl =
		"ssld cannot setup ssl, check your certificates and private key";
	static const char *no_ssl_or_zlib =
		"ssld has neither SSL/TLS or zlib support killing all sslds";
	rb_dlink_node *ptr, *next;
	ssl_ctl_buf_t *ctl_buf;
	if(ctl->dead)
		return;
	RB_DLINK_FOREACH_SAFE(ptr, next, ctl->readq.head)
	{
		ctl_buf = ptr->data;
		switch (*ctl_buf->buf)
		{
		case 'N':
			ircd_ssl_ok = 0;
			break;
		case 'D':
			ssl_process_dead_fd(ctl, ctl_buf);
			break;
		case 'S':
			ssl_process_zipstats(ctl, ctl_buf);
			break;
		case 'I':
			ircd_ssl_ok = 0;
			ilog(L_MAIN, "%s", cannot_setup_ssl);
			sendto_realops_flags(UMODE_ALL, L_ALL, "%s", cannot_setup_ssl);
		case 'U':
			zlib_ok = 0;
			ircd_ssl_ok = 0;
			ilog(L_MAIN, "%s", no_ssl_or_zlib);
			sendto_realops_flags(UMODE_ALL, L_ALL, "%s", no_ssl_or_zlib);
			ssl_killall();
			break;
		case 'z':
			zlib_ok = 0;
			break;
		default:
			ilog(L_MAIN, "Received invalid command from ssld: %s", ctl_buf->buf);
			sendto_realops_flags(UMODE_ALL, L_ALL,
					     "Received invalid command from ssld");
			break;
		}
		rb_dlinkDelete(ptr, &ctl->readq);
		rb_free(ctl_buf->buf);
		rb_free(ctl_buf);
	}

}

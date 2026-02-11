mod_process_cmd_recv(mod_ctl_t * ctl)
{
	rb_dlink_node *ptr, *next;
	mod_ctl_buf_t *ctl_buf;

	RB_DLINK_FOREACH_SAFE(ptr, next, ctl->readq.head)
	{
		ctl_buf = ptr->data;

		switch (*ctl_buf->buf)
		{
		case 'A':
			{
				if (ctl_buf->nfds != 2 || ctl_buf->buflen != 5)
				{
					cleanup_bad_message(ctl, ctl_buf);
					break;
				}

				if(!ssl_ok)
				{
					send_nossl_support(ctl, ctl_buf);
					break;
				}
				ssl_process_accept(ctl, ctl_buf);
				break;
			}
		case 'C':
			{
				if (ctl_buf->nfds != 2 || ctl_buf->buflen != 5)
				{
					cleanup_bad_message(ctl, ctl_buf);
					break;
				}

				if(!ssl_ok)
				{
					send_nossl_support(ctl, ctl_buf);
					break;
				}
				ssl_process_connect(ctl, ctl_buf);
				break;
			}

		case 'K':
			{
				if(!ssl_ok)
				{
					send_nossl_support(ctl, ctl_buf);
					break;
				}
				ssl_new_keys(ctl, ctl_buf);
				break;
			}
		case 'I':
			init_prng(ctl, ctl_buf);
			break;
		case 'S':
			{
				process_stats(ctl, ctl_buf);
				break;
			}
		case 'Y':
			{
				change_connid(ctl, ctl_buf);
				break;
			}

#ifdef HAVE_LIBZ
		case 'Z':
			{
				if (ctl_buf->nfds != 2 || ctl_buf->buflen < 6)
				{
					cleanup_bad_message(ctl, ctl_buf);
					break;
				}


				zlib_process(ctl, ctl_buf);
				break;
			}
#else

		case 'Z':
			send_nozlib_support(ctl, ctl_buf);
			break;

#endif
		default:
			break;

		}
		rb_dlinkDelete(ptr, &ctl->readq);
		rb_free(ctl_buf->buf);
		rb_free(ctl_buf);
	}

}

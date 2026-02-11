rb_linebuf_flush(rb_fde_t *F, buf_head_t * bufhead)
{
	buf_line_t *bufline;
	int retval;


#ifdef HAVE_WRITEV
	if(!rb_fd_ssl(F))
	{
		rb_dlink_node *ptr;
		int x = 0, y;
		int xret;
		static struct rb_iovec vec[RB_UIO_MAXIOV];

		memset(vec, 0, sizeof(vec));

		if(bufhead->list.head == NULL)
		{

			errno = EWOULDBLOCK;
			return -1;
		}

		ptr = bufhead->list.head;

		bufline = ptr->data;
		if(!bufline->terminated)
		{
			errno = EWOULDBLOCK;
			return -1;

		}

		vec[x].iov_base = bufline->buf + bufhead->writeofs;
		vec[x++].iov_len = bufline->len - bufhead->writeofs;
		ptr = ptr->next;

		do
		{
			if(ptr == NULL)
				break;

			bufline = ptr->data;
			if(!bufline->terminated)
				break;

			vec[x].iov_base = bufline->buf;
			vec[x].iov_len = bufline->len;
			ptr = ptr->next;

		}
		while(++x < RB_UIO_MAXIOV);

		if(x == 0)
		{
			errno = EWOULDBLOCK;
			return -1;
		}

		xret = retval = rb_writev(F, vec, x);
		if(retval <= 0)
			return retval;

		ptr = bufhead->list.head;

		for(y = 0; y < x; y++)
		{
			bufline = ptr->data;

			if(xret >= bufline->len - bufhead->writeofs)
			{
				xret -= bufline->len - bufhead->writeofs;
				ptr = ptr->next;
				rb_linebuf_done_line(bufhead, bufline, bufhead->list.head);
				bufhead->writeofs = 0;
			}
			else
			{
				bufhead->writeofs += xret;
				break;
			}
		}

		return retval;
	}
#endif


	if(bufhead->list.head == NULL)
	{

		errno = EWOULDBLOCK;
		return -1;
	}

	bufline = bufhead->list.head->data;


	if(!bufline->terminated)
	{
		errno = EWOULDBLOCK;
		return -1;
	}


	retval = rb_write(F, bufline->buf + bufhead->writeofs, bufline->len - bufhead->writeofs);

	if(retval <= 0)
		return retval;


	bufhead->writeofs += retval;


	if(bufhead->writeofs == bufline->len)
	{
		bufhead->writeofs = 0;
		lrb_assert(bufhead->len >= 0);
		rb_linebuf_done_line(bufhead, bufline, bufhead->list.head);
	}


	return retval;
}

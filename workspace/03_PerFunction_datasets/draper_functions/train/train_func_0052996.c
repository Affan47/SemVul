afs_send_pages(struct afs_call *call, struct msghdr *msg,
			  struct kvec *iov)
{
	struct page *pages[8];
	unsigned count, n, loop, offset, to;
	pgoff_t first = call->first, last = call->last;
	int ret;

	_enter("");

	offset = call->first_offset;
	call->first_offset = 0;

	do {
		_debug("attach %lx-%lx", first, last);

		count = last - first + 1;
		if (count > ARRAY_SIZE(pages))
			count = ARRAY_SIZE(pages);
		n = find_get_pages_contig(call->mapping, first, count, pages);
		ASSERTCMP(n, ==, count);

		loop = 0;
		do {
			msg->msg_flags = 0;
			to = PAGE_SIZE;
			if (first + loop >= last)
				to = call->last_to;
			else
				msg->msg_flags = MSG_MORE;
			iov->iov_base = kmap(pages[loop]) + offset;
			iov->iov_len = to - offset;
			offset = 0;

			_debug("- range %u-%u%s",
			       offset, to, msg->msg_flags ? " [more]" : "");
			iov_iter_kvec(&msg->msg_iter, WRITE | ITER_KVEC,
				      iov, 1, to - offset);


			if (first + loop >= last)
				call->state = AFS_CALL_AWAIT_REPLY;
			ret = rxrpc_kernel_send_data(call->rxcall, msg,
						     to - offset);
			kunmap(pages[loop]);
			if (ret < 0)
				break;
		} while (++loop < count);
		first += count;

		for (loop = 0; loop < count; loop++)
			put_page(pages[loop]);
		if (ret < 0)
			break;
	} while (first <= last);

	_leave(" = %d", ret);
	return ret;
}

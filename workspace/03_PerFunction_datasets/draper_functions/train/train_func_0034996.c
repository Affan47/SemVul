writetochild(struct connection *p)
{
	size_t bytestowrite;
	ssize_t r;

	bytestowrite = p->client_input.end - p->client_input.start;
	if (bytestowrite == 0) {
		log_d("writetochild: bytestowrite is zero!");
		return 0;
	}
	r = write(p->rfd, p->client_input.start, bytestowrite);
	if (debug)
		log_d("writetochild: %d %d %u %d", p->rfd, (int) (p->client_input.start - p->client_input.floor), (unsigned) bytestowrite, (int) r);
	switch (r) {
	case -1:
		if (errno == EAGAIN)
			return 0;
		if (debug)
			lerror("write");
		close_connection(p);
		return -1;
	default:
		p->t = current_time;
		p->client_input.start += r;
		if (p->client_input.start == p->client_input.end)
			p->client_input.start = p->client_input.end = p->client_input.floor;
		break;
	}
	return 0;
}

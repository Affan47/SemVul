pipe_run(struct connection *p)
{
	short cevents, pevents;
	int canwritetoclient, canwritetochild;

	cevents = p->pollno != -1 ? pollfds[p->pollno].revents : 0;
	pevents = p->rpollno != -1 ? pollfds[p->rpollno].revents : 0;
	if (cevents & POLLERR || cevents == POLLHUP) {
		close_connection(p);
		return;
	}
	if (pevents & POLLERR || pevents == POLLHUP) {
		close_connection(p);
		return;
	}
	canwritetoclient = cevents & POLLOUT || p->output.end == p->output.floor;
	canwritetochild = pevents & POLLOUT || p->client_input.end == p->client_input.floor;
	if (cevents & POLLIN)
		if (readfromclient(p) == -1)
			return;
	if (pevents & POLLIN)
		if (readfromchild(p) == -1)
			return;
	if (p->script_input.end && p->pipe_params.state != 2)
		if (scanlflf(p) == -1)
			return;
	if (p->pipe_params.state == 2 && p->script_input.start < p->script_input.end)
		copychunk(p);
	if (p->script_input.state == 2)
		copylastchunk(p);
	if (p->output.end > p->output.start && canwritetoclient)
		if (writetoclient(p) == -1)
			return;
	if (p->client_input.end > p->client_input.start && canwritetochild)
		if (writetochild(p) == -1)
			return;
	if (childisfinished(p)) {
		if (p->keepalive) {
			if (p->client_input.end > p->client_input.start) {
				log_d("client_input is not empty");
				close_connection(p);
			} else
				reinit_connection(p);
		} else
			close_connection(p);
	}
}

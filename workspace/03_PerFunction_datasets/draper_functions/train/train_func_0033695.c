idnsSendQuery(idns_query * q)
{
    int x;
    int ns;
    if (DnsSocket < 0) {
	debug(78, 1) ("idnsSendQuery: Can't send query, no DNS socket!\n");
	return;
    }

    assert(nns > 0);
    assert(q->lru.next == NULL);
    assert(q->lru.prev == NULL);
    idnsTcpCleanup(q);
  try_again:
    ns = q->nsends % nns;
    x = comm_udp_sendto(DnsSocket,
	&nameservers[ns].S,
	sizeof(nameservers[ns].S),
	q->buf,
	q->sz);
    q->nsends++;
    q->queue_t = q->sent_t = current_time;
    if (x < 0) {
	debug(50, 1) ("idnsSendQuery: FD %d: sendto: %s\n",
	    DnsSocket, xstrerror());
	if (q->nsends % nns != 0)
	    goto try_again;
    } else {
	fd_bytes(DnsSocket, x, FD_WRITE);
	commSetSelect(DnsSocket, COMM_SELECT_READ, idnsRead, NULL, 0);
    }
    nameservers[ns].nqueries++;
    dlinkAdd(q, &q->lru, &lru_list);
    idnsTickleQueue();
}

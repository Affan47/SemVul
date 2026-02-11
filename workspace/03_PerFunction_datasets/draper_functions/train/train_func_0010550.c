__ncptcp_try_send(struct ncp_server *server)
{
	struct ncp_request_reply *rq;
	struct kvec *iov;
	struct kvec iovc[3];
	int result;

	rq = server->tx.creq;
	if (!rq)
		return;


	memcpy(iovc, rq->tx_ciov, rq->tx_iovlen * sizeof(iov[0]));
	result = do_send(server->ncp_sock, iovc, rq->tx_iovlen,
			 rq->tx_totallen, MSG_NOSIGNAL | MSG_DONTWAIT);

	if (result == -EAGAIN)
		return;

	if (result < 0) {
		pr_err("tcp: Send failed: %d\n", result);
		__ncp_abort_request(server, rq, result);
		return;
	}
	if (result >= rq->tx_totallen) {
		server->rcv.creq = rq;
		server->tx.creq = NULL;
		return;
	}
	rq->tx_totallen -= result;
	iov = rq->tx_ciov;
	while (iov->iov_len <= result) {
		result -= iov->iov_len;
		iov++;
		rq->tx_iovlen--;
	}
	iov->iov_base += result;
	iov->iov_len -= result;
	rq->tx_ciov = iov;
}

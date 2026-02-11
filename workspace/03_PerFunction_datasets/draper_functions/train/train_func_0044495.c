neighborsCount(request_t * request)
{
    peer *p = NULL;
    int count = 0;
    for (p = Config.peers; p; p = p->next)
	if (peerWouldBePinged(p, request))
	    count++;
    debug(15, 3) ("neighborsCount: %d\n", count);
    return count;
}

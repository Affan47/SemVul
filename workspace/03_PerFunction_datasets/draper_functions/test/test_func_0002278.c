ssl2_StartGatherBytes(sslSocket *ss, sslGather *gs, unsigned int count)
{
    int rv;

    PORT_Assert( ss->opt.noLocks || ssl_HaveRecvBufLock(ss) );
    gs->state     = GS_DATA;
    gs->remainder = count;
    gs->count     = count;
    gs->offset    = 0;
    if (count > gs->buf.space) {
	rv = sslBuffer_Grow(&gs->buf, count);
	if (rv) {
	    return rv;
	}
    }
    return ssl2_GatherData(ss, gs, 0);
}

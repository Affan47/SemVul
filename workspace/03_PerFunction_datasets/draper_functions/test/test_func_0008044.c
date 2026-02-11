dvb_ringbuffer_pkt_dispose(struct dvb_ringbuffer *rbuf, size_t idx)
{
	size_t pktlen;

	rbuf->data[(idx + 2) % rbuf->size] = PKT_DISPOSED;


	while(dvb_ringbuffer_avail(rbuf) > DVB_RINGBUFFER_PKTHDRSIZE) {
		if (DVB_RINGBUFFER_PEEK(rbuf, 2) == PKT_DISPOSED) {
			pktlen = DVB_RINGBUFFER_PEEK(rbuf, 0) << 8;
			pktlen |= DVB_RINGBUFFER_PEEK(rbuf, 1);
			DVB_RINGBUFFER_SKIP(rbuf, pktlen + DVB_RINGBUFFER_PKTHDRSIZE);
		} else {

			break;
		}
	}
}

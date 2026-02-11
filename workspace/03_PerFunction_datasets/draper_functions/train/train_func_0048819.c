z_compress(void *arg, unsigned char *rptr, unsigned char *obuf,
	       int isize, int osize)
{
	struct ppp_deflate_state *state = (struct ppp_deflate_state *) arg;
	int r, proto, off, olen, oavail;
	unsigned char *wptr;


	proto = PPP_PROTOCOL(rptr);
	if (proto > 0x3fff || proto == 0xfd || proto == 0xfb)
		return 0;


	if (osize > isize)
		osize = isize;

	wptr = obuf;


	wptr[0] = PPP_ADDRESS(rptr);
	wptr[1] = PPP_CONTROL(rptr);
	put_unaligned_be16(PPP_COMP, wptr + 2);
	wptr += PPP_HDRLEN;
	put_unaligned_be16(state->seqno, wptr);
	wptr += DEFLATE_OVHD;
	olen = PPP_HDRLEN + DEFLATE_OVHD;
	state->strm.next_out = wptr;
	state->strm.avail_out = oavail = osize - olen;
	++state->seqno;

	off = (proto > 0xff) ? 2 : 3;
	rptr += off;
	state->strm.next_in = rptr;
	state->strm.avail_in = (isize - off);

	for (;;) {
		r = zlib_deflate(&state->strm, Z_PACKET_FLUSH);
		if (r != Z_OK) {
			if (state->debug)
				printk(KERN_ERR
				       "z_compress: deflate returned %d\n", r);
			break;
		}
		if (state->strm.avail_out == 0) {
			olen += oavail;
			state->strm.next_out = NULL;
			state->strm.avail_out = oavail = 1000000;
		} else {
			break;
		}
	}
	olen += oavail - state->strm.avail_out;


	if (olen < isize && olen <= osize) {
		state->stats.comp_bytes += olen;
		state->stats.comp_packets++;
	} else {
		state->stats.inc_bytes += isize;
		state->stats.inc_packets++;
		olen = 0;
	}
	state->stats.unc_bytes += isize;
	state->stats.unc_packets++;

	return olen;
}

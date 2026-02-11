xdrrec_eof(XDR *xdrs)
{

	RECSTREAM *rstrm = (RECSTREAM *)(xdrs->x_private);

	if (rstrm->in_nonblock) {


		return (rstrm->in_needpoll);
	}
	while (rstrm->fbtbc > 0 || (!rstrm->last_frag)) {
		if (!skip_input_bytes(rstrm, rstrm->fbtbc))
			return (TRUE);
		rstrm->fbtbc = 0;
		if ((!rstrm->last_frag) && (!set_input_fragment(rstrm)))
			return (TRUE);
	}
	if (rstrm->in_finger == rstrm->in_boundry)
		return (TRUE);
	return (FALSE);
}

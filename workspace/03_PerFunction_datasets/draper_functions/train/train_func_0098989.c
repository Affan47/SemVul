xdrrec_putint32(XDR *xdrs, int32_t *ip)
{

	RECSTREAM *rstrm = (RECSTREAM *)(xdrs->x_private);

	int32_t *dest_lp = ((int32_t *)(rstrm->out_finger));

	if ((rstrm->out_finger += sizeof (int32_t)) > rstrm->out_boundry) {


		rstrm->out_finger -= sizeof (int32_t);
		rstrm->frag_sent = TRUE;
		if (!flush_out(rstrm, FALSE))
			return (FALSE);

		dest_lp = ((int32_t *)(rstrm->out_finger));
		rstrm->out_finger += sizeof (int32_t);
	}
	*dest_lp = (int32_t)xdr_hton32((uint32_t)(*ip));
	return (TRUE);
}

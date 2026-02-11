gigaset_isoc_buildframe(struct bc_state *bcs, unsigned char *in, int len)
{
	int result;

	switch (bcs->proto2) {
	case L2_HDLC:
		result = hdlc_buildframe(bcs->hw.bas->isooutbuf, in, len);
		gig_dbg(DEBUG_ISO, "%s: %d bytes HDLC -> %d",
			__func__, len, result);
		break;
	default:
		result = trans_buildframe(bcs->hw.bas->isooutbuf, in, len);
		gig_dbg(DEBUG_ISO, "%s: %d bytes trans -> %d",
			__func__, len, result);
	}
	return result;
}

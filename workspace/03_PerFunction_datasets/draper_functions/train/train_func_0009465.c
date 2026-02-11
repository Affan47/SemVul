aim_tx_sendframe(aim_session_t *sess, aim_frame_t *fr)
{
	if (fr->hdrtype == AIM_FRAMETYPE_FLAP)
		return sendframe_flap(sess, fr);
	else if (fr->hdrtype == AIM_FRAMETYPE_OFT)
		return sendframe_rendezvous(sess, fr);
	return -1;
}

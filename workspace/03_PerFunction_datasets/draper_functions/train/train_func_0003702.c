gst_rtp_sbc_pay_get_frame_len(gint subbands, gint channels,
		gint blocks, gint bitpool, const gchar *channel_mode)
{
	gint len;
	gint join;

	len = 4 + (4 * subbands * channels)/8;

	if (strcmp(channel_mode, "mono") == 0 ||
		strcmp(channel_mode, "dual") == 0)
		len += ((blocks * channels * bitpool) + 7) / 8;
	else {
		join = strcmp(channel_mode, "joint") == 0 ? 1 : 0;
		len += ((join * subbands + blocks * bitpool) + 7) / 8;
	}

	return len;
}

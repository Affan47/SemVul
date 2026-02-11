gf_media_format_ttxt_sdp(GP_RTPPacketizer *builder, char *payload_name, char *sdpLine, GF_ISOFile *file, u32 track)
{
	char buffer[2000];
	u32 w, h, i, m_w, m_h;
	s32 tx, ty;
	s16 l;
	sprintf(sdpLine, "a=fmtp:%d sver=60; ", builder->PayloadType);
	gf_isom_get_track_layout_info(file, track, &w, &h, &tx, &ty, &l);
	sprintf(buffer, "width=%d; height=%d; tx=%d; ty=%d; layer=%d; ", w, h, tx, ty, l);
	strcat(sdpLine, buffer);
	m_w = w;
	m_h = h;
	for (i=0; i<gf_isom_get_track_count(file); i++) {
		switch (gf_isom_get_media_type(file, i+1)) {
		case GF_ISOM_MEDIA_SCENE:
		case GF_ISOM_MEDIA_VISUAL:
			gf_isom_get_track_layout_info(file, i+1, &w, &h, &tx, &ty, &l);
			if (w>m_w) m_w = w;
			if (h>m_h) m_h = h;
			break;
		default:
			break;
		}
	}
	sprintf(buffer, "max-w=%d; max-h=%d", m_w, m_h);
	strcat(sdpLine, buffer);

	strcat(sdpLine, "; tx3g=");
	for (i=0; i<gf_isom_get_sample_description_count(file, track); i++) {
		char *tx3g;
		u32 tx3g_len, len;
		gf_isom_text_get_encoded_tx3g(file, track, i+1, GF_RTP_TX3G_SIDX_OFFSET, &tx3g, &tx3g_len);
		len = gf_base64_encode(tx3g, tx3g_len, buffer, 2000);
		gf_free(tx3g);
		buffer[len] = 0;
		if (i) strcat(sdpLine, ", ");
		strcat(sdpLine, buffer);
	}
}

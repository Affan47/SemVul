add_empty_calltoken_ie(struct chan_iax2_pvt *pvt, struct iax_ie_data *ied)
{

	if (pvt && ied && (2 < ((int) sizeof(ied->buf) - ied->pos))) {
		ied->buf[ied->pos++] = IAX_IE_CALLTOKEN;
		ied->buf[ied->pos++] = 0;
		pvt->calltoken_ie_len = 2;
	}
}

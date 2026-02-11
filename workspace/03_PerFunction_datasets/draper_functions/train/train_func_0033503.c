ews_oab_decoder_decode (EwsOabDecoder *eod,
                        EwsOabContactAddedCb cb,
                        gpointer user_data,
                        GCancellable *cancellable,
                        GError **error)
{
	EwsOabDecoderPrivate *priv = GET_PRIVATE (eod);
	GError *err = NULL;
	EwsOabHdr *o_hdr;
	gboolean ret = TRUE;

	o_hdr = ews_read_oab_header (eod, cancellable, &err);
	if (!o_hdr) {
		ret = FALSE;
		goto exit;
	}

	priv->total_records = o_hdr->total_recs;
	g_print ("Total records is %d \n", priv->total_records);

	ret = ews_decode_metadata (eod, cancellable, &err);
	if (!ret)
		goto exit;

	ret = ews_decode_and_store_oab_records (
		eod, cb, user_data, cancellable, &err);
exit:
	if (o_hdr)
		g_free (o_hdr);

	if (err)
		g_propagate_error (error, err);

	return ret;
}

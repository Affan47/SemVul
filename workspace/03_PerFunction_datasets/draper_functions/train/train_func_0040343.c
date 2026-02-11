atlv_free (Atlv *tlv)
{
	if (!tlv)
		return;


	atlv_free (tlv->child);
	atlv_free (tlv->next);


	if (tlv->decoded)
		g_bytes_unref (tlv->decoded);
	if (tlv->value)
		g_bytes_unref (tlv->value);

	g_slice_free (Atlv, tlv);
}

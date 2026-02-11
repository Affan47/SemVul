midgard_blob_new (MidgardObject *attachment, const gchar *encoding)
{
	g_return_val_if_fail (attachment != NULL, NULL);

	MidgardBlob *self = g_object_new (MIDGARD_TYPE_BLOB,
		"attachment", attachment, "encoding", encoding ? encoding : "UTF-8", NULL);

	return self;
}

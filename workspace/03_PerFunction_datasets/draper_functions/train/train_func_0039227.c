_g_mime_object_set_content_disposition (GMimeObject *object, GMimeContentDisposition *disposition)
{
	if (object->disposition) {
		g_mime_event_remove (object->disposition->priv, (GMimeEventCallback) content_disposition_changed, object);
		g_object_unref (object->disposition);
	}

	g_mime_event_add (disposition->priv, (GMimeEventCallback) content_disposition_changed, object);
	object->disposition = disposition;
	g_object_ref (disposition);
}

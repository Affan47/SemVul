add_attach (icalcomponent *icalcomp,
            const gchar *uri)
{
	gsize buf_size;
	gchar *buf;
	icalproperty *prop;
	icalattach *attach;

	g_return_if_fail (icalcomp != NULL);
	g_return_if_fail (uri != NULL);

	buf_size = 2 * strlen (uri);
	buf = g_malloc0 (buf_size);
	icalvalue_encode_ical_string (uri, buf, buf_size);
	attach = icalattach_new_from_url (uri);
	prop = icalproperty_new_attach (attach);
	icalcomponent_add_property (icalcomp, prop);
	icalattach_unref (attach);
	g_free (buf);
}

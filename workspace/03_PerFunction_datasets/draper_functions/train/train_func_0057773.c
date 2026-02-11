e_soap_message_write_base64 (ESoapMessage *msg,
                             const gchar *string,
                             gint len)
{
	gchar *encoded;

	g_return_if_fail (E_IS_SOAP_MESSAGE (msg));

	encoded = g_base64_encode ((const guchar *) string, len);
	e_soap_message_write_string (msg, encoded);
	g_free (encoded);
}

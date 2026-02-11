e_soap_message_add_namespace (ESoapMessage *msg,
                              const gchar *prefix,
                              const gchar *ns_uri)
{
	g_return_if_fail (E_IS_SOAP_MESSAGE (msg));

	if (ns_uri == NULL)
		ns_uri = "";

	xmlNewNs (
		msg->priv->last_node,
		(const xmlChar *) ns_uri,
		(const xmlChar *) prefix);
}

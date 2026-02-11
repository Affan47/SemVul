e_soap_response_get_next_parameter (ESoapResponse *response,
                                    ESoapParameter *from)
{
	GList *l;

	g_return_val_if_fail (E_IS_SOAP_RESPONSE (response), NULL);
	g_return_val_if_fail (from != NULL, NULL);

	l = g_list_find (response->priv->parameters, (gconstpointer) from);
	if (!l)
		return NULL;

	return l->next ? (ESoapParameter *) l->next->data : NULL;
}

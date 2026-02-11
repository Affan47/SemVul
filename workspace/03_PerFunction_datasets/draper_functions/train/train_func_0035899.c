http_post_connected(MsnConnection *mc)
{
	char buf[4096];
	char soap_action[512];

	LList *l =
		l_list_find_custom(http_connection_list, mc, http_mc_compare);

	HttpData *data = (HttpData *)l->data;

	if (data->soap_action) {
		snprintf(soap_action, sizeof(soap_action), "SOAPAction: %s\r\n", data->soap_action);
	} else {
		soap_action[0] = '\0';
	}

	snprintf(buf, sizeof(buf), "POST %s HTTP/1.1\r\n" "%s"

		"Content-Type: text/xml; charset=utf-8\r\n"
		"User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1)\r\n"
		"Host: %s\r\n"
		"Content-Length: %d\r\n"
		"%s"
		"\r\n"
		"%s",
		data->path,
		soap_action,
		mc->host,
		(int)(strlen(data->request)), data->params, data->request);

	msn_connection_send_data(mc, buf, strlen(buf));
}

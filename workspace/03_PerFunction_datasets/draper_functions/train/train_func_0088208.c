iks_sasl_challenge (struct stream_data *data, iks *challenge)
{
	char *message;
	iks *x;
	char *tmp;

	tmp = iks_cdata (iks_child (challenge));
	if (!tmp) return;


	message = iks_base64_decode (tmp);
	if (!message) return;


	if (strstr (message, "rspauth")) {
		x = iks_new ("response");
	} else {
		x = make_sasl_response (data, message);
	}
	if (x) {
		iks_insert_attrib (x, "xmlns", IKS_NS_XMPP_SASL);
		iks_send (data->prs, x);
		iks_delete (x);
	}
	iks_free (message);
}

respond(ns_client_t *client, isc_result_t result) {
	isc_result_t msg_result;

	msg_result = dns_message_reply(client->message, ISC_TRUE);
	if (msg_result != ISC_R_SUCCESS)
		goto msg_failure;
	client->message->rcode = dns_result_torcode(result);

	ns_client_send(client);
	return;

 msg_failure:
	isc_log_write(ns_g_lctx, NS_LOGCATEGORY_UPDATE, NS_LOGMODULE_UPDATE,
		      ISC_LOG_ERROR,
		      "could not create update response message: %s",
		      isc_result_totext(msg_result));
	ns_client_next(client, msg_result);
}

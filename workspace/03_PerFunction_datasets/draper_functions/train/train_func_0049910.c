finish_active_slot(struct active_request_slot *slot)
{
	closedown_active_slot(slot);
	curl_easy_getinfo(slot->curl, CURLINFO_HTTP_CODE, &slot->http_code);

	if (slot->finished != NULL)
		(*slot->finished) = 1;


	if (slot->results != NULL) {
		slot->results->curl_result = slot->curl_result;
		slot->results->http_code = slot->http_code;
	}


	if (slot->callback_func != NULL)
		slot->callback_func(slot->callback_data);
}

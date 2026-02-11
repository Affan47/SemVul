fetch_alternates(struct walker *walker, const char *base)
{
	struct strbuf buffer = STRBUF_INIT;
	char *url;
	struct active_request_slot *slot;
	struct alternates_request alt_req;
	struct walker_data *cdata = walker->data;


#ifdef USE_CURL_MULTI
	while (cdata->got_alternates == 0) {
		step_active_slots();
	}
#endif


	if (cdata->got_alternates == 1)
		return;


	cdata->got_alternates = 0;

	if (walker->get_verbosely)
		fprintf(stderr, "Getting alternates list for %s\n", base);

	url = xmalloc(strlen(base) + 31);
	sprintf(url, "%s/objects/info/http-alternates", base);


	slot = get_active_slot();
	slot->callback_func = process_alternates_response;
	alt_req.walker = walker;
	slot->callback_data = &alt_req;

	curl_easy_setopt(slot->curl, CURLOPT_FILE, &buffer);
	curl_easy_setopt(slot->curl, CURLOPT_WRITEFUNCTION, fwrite_buffer);
	curl_easy_setopt(slot->curl, CURLOPT_URL, url);

	alt_req.base = base;
	alt_req.url = url;
	alt_req.buffer = &buffer;
	alt_req.http_specific = 1;
	alt_req.slot = slot;

	if (start_active_slot(slot))
		run_active_slot(slot);
	else
		cdata->got_alternates = -1;

	strbuf_release(&buffer);
	free(url);
}

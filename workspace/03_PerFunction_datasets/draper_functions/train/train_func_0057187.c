smug_logout(struct session *session)
{
	char url[500];
	struct smug_curl_buffer *curl_buf;
	CURL *curl = NULL;
	CURLcode res;

	if (!session)
		return -EINVAL;

	curl_buf = smug_curl_buffer_alloc();
	if (!curl_buf)
		return -ENOMEM;

	curl = curl_init();
	if (!curl)
		return -EINVAL;

	sprintf(url, smugmug_logout_url, session->session_id, api_key);
	dbg("url = %s\n", url);

	curl_set_cookie(curl, session->su_cookie);
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, curl_buf);
	res = curl_easy_perform(curl);
	if (res) {
		fprintf(stderr, "error(%d) trying to logout\n", res);
		return -EINVAL;
	}

	curl_easy_cleanup(curl);
	smug_curl_buffer_free(curl_buf);
	return 0;
}

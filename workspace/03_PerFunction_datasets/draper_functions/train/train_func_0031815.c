do_server_stuff(const char * key, GMarkupParseContext * parser) {
    char * url;
    CURL* handle;
    char curl_error_buffer[CURL_ERROR_SIZE];

    handle = curl_easy_init();

    curl_easy_setopt(handle, CURLOPT_NOPROGRESS, TRUE);
    curl_easy_setopt(handle, CURLOPT_NOSIGNAL, TRUE);
    curl_easy_setopt(handle, CURLOPT_AUTOREFERER, TRUE);
    curl_easy_setopt(handle, CURLOPT_ENCODING, "");
#ifdef CURLOPT_MAXFILESIZE
    curl_easy_setopt(handle, CURLOPT_MAXFILESIZE, MAX_RESPONSE_SIZE);
#endif
    curl_easy_setopt(handle, CURLOPT_ERRORBUFFER, curl_error_buffer);

    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, libcurl_gmarkup_glue);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, parser);
    url = activation_url(key);
    curl_easy_setopt(handle, CURLOPT_URL, url);

    if (curl_easy_perform(handle) != 0) {
        g_error("Problem fetching data from server:\n%s",
                curl_error_buffer);
        exit(EXIT_FAILURE);
    }

    g_free(url);
}

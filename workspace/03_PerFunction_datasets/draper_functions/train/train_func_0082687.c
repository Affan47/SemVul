set_dlopts_from_options(struct options_t *options,
						struct download_opts_t *dlopts)
{


    if((options == NULL) || (dlopts == NULL)) {
	return NULL;
    }

    if(options->bandwidth) {
	dlopts->bandwidth = options->bandwidth;
    }

    if(options->no_passive_ftp_f) {
	dlopts->no_passive_ftp = 1;
    }

    if(options->speed) {
	dlopts->speed = strdup(options->speed);
    }

    if(options->range) {
	dlopts->range = strdup(options->range);
    }

    if(options->byterange) {
	dlopts->byterange = strdup(options->byterange);
    }

    if(options->auto_retry_times) {
	dlopts->auto_retry = options->auto_retry_times;
    }

    if(options->stream_timeout) {
	dlopts->stream_timeout = strdup(options->stream_timeout);
    }

    if(options->resume) {
	dlopts->resume_download = 1;
    }

    if(options->username) {
	dlopts->username = strdup(options->username);
    }

    if(options->password) {
	dlopts->password = strdup(options->password);
    }

    if(options->http_proxy) {
	dlopts->http_proxy = strdup(options->http_proxy);
    }

    return dlopts;
}

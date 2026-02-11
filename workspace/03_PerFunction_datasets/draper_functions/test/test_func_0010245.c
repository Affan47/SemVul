transport_get(struct remote *remote, const char *url)
{
	struct transport *ret = xcalloc(1, sizeof(*ret));

	ret->remote = remote;
	ret->url = url;

	if (!prefixcmp(url, "rsync://")) {
		ret->get_refs_list = get_refs_via_rsync;
		ret->fetch = fetch_objs_via_rsync;
		ret->push = rsync_transport_push;

	} else if (!prefixcmp(url, "http://")
	        || !prefixcmp(url, "https://")
	        || !prefixcmp(url, "ftp://")) {
#ifdef NO_CURL
		error("git was compiled without libcurl support.");
#else
		ret->get_refs_list = get_refs_via_curl;
		ret->fetch = fetch_objs_via_curl;
		ret->push = curl_transport_push;
#endif
		ret->disconnect = disconnect_walker;

	} else if (is_local(url) && is_file(url)) {
		struct bundle_transport_data *data = xcalloc(1, sizeof(*data));
		ret->data = data;
		ret->get_refs_list = get_refs_from_bundle;
		ret->fetch = fetch_refs_from_bundle;
		ret->disconnect = close_bundle;

	} else {
		struct git_transport_data *data = xcalloc(1, sizeof(*data));
		ret->data = data;
		ret->set_option = set_git_option;
		ret->get_refs_list = get_refs_via_connect;
		ret->fetch = fetch_refs_via_pack;
		ret->push = git_transport_push;
		ret->disconnect = disconnect_git;

		data->thin = 1;
		data->conn = NULL;
		data->uploadpack = "git-upload-pack";
		if (remote && remote->uploadpack)
			data->uploadpack = remote->uploadpack;
		data->receivepack = "git-receive-pack";
		if (remote && remote->receivepack)
			data->receivepack = remote->receivepack;
	}

	return ret;
}

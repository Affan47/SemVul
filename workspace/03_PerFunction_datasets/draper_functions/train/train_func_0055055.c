wget_connect(struct wgetfile *finfo)
{
	extern struct cfg global_cfg;
	const char *host, *port;

	if(finfo->proto == HTTP && global_cfg.http_proxy){
		host = global_cfg.http_proxy;
		port = global_cfg.http_proxy_port;
	}else{
		host = finfo->host_name;
		port = finfo->host_port;
	}

	finfo->sock = connection_fd(host, port);

	if(finfo->sock == -1){
		finfo->sock = dial(host, port);
		if(finfo->sock == -1)
			return 1;
		connection_add(finfo->sock, host, port);
	}else{
		output_err(OUT_INFO, "Reusing connection to %s:%s", host, port);
	}
	return 0;
}

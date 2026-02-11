search_gui_browse(const gchar *host, guint16 port, guint32 flags)
{
	struct browse_request *req;

	WALLOC(req);
	req->host = atom_str_get(host);
	req->port = port;
	req->flags = flags;
	guc_adns_resolve(req->host, search_gui_browse_helper, req);
}

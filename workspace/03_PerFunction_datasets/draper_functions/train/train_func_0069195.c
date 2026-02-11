download_request_free(struct download_request **req_ptr)
{
	struct download_request *req;

	g_assert(req_ptr);

	req = *req_ptr;
	g_assert(req);

	*req_ptr = NULL;
	atom_str_free_null(&req->uri);
	atom_sha1_free_null(&req->sha1);
	atom_tth_free_null(&req->tth);
	atom_str_free_null(&req->hostname);
	atom_str_free_null(&req->filename);
	atom_str_free_null(&req->parq_id);
	atom_guid_free_null(&req->guid);
	gnet_host_vec_free(&req->proxies);
	if (req->fi) {
		g_assert(req->fi->refcount > 0);
		req->fi->refcount--;
	}
	WFREE(req);
}

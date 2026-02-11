gf_term_is_supported_url(GF_Terminal *term, const char *fileName, Bool use_parent_url, Bool no_mime_check)
{
	GF_InputService *ifce;
	GF_Err e;
	char *sURL;
	char *parent_url = NULL;
	if (use_parent_url && term->root_scene) parent_url = term->root_scene->root_od->net_service->url;

	ifce = gf_term_can_handle_service(term, fileName, parent_url, no_mime_check, &sURL, &e, NULL);
	if (!ifce) return 0;
	gf_modules_close_interface((GF_BaseInterface *) ifce);
	gf_free(sURL);
	return 1;
}

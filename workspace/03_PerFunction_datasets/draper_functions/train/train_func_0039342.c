gf_term_relocate_url(GF_Terminal *term, const char *service_url, const char *parent_url, char *out_relocated_url, char *out_localized_url)
{
	u32 i, count;

	i=0;
	count = gf_list_count(term->uri_relocators);
	for (i=0; i<count; i++) {
		Bool result;
		GF_URIRelocator *uri_relocator = gf_list_get(term->uri_relocators, i);
		result = uri_relocator->relocate_uri(uri_relocator, parent_url, service_url, out_relocated_url, out_localized_url);
		if (result) return 1;
	}
	return 0;
}

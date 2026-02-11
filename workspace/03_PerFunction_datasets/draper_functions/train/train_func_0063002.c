xlsx_write_hlink (GnmHLink const *link, GSList *ranges, XLSXClosure *info)
{
	gchar const *target = gnm_hlink_get_target (link);
	gchar const *location = NULL;
	gchar const *rid = NULL;
	gchar const *tip;
	GType const t = G_OBJECT_TYPE (link);

	if (t == gnm_hlink_url_get_type () ||
	    t == gnm_hlink_email_get_type ()) {
		rid = gsf_outfile_open_pkg_add_extern_rel (
			GSF_OUTFILE_OPEN_PKG (gsf_xml_out_get_output (info->xml)),
			target, ns_rel_hlink);
	} else if (t != gnm_hlink_cur_wb_get_type ())
		return;

	for (; ranges  != NULL ; ranges = ranges->next) {
		gsf_xml_out_start_element (info->xml, "hyperlink");
		xlsx_add_range (info->xml, "ref", ranges->data);

		if (t == gnm_hlink_cur_wb_get_type ())
			gsf_xml_out_add_cstr (info->xml, "location", target);
		else if (NULL != rid)
			gsf_xml_out_add_cstr (info->xml, "r:id", rid);
		if (NULL != location)
			gsf_xml_out_add_cstr (info->xml, "tooltip", location);
		if (NULL != (tip = gnm_hlink_get_tip (link)))
			gsf_xml_out_add_cstr (info->xml, "tooltip", tip);
		gsf_xml_out_end_element (info->xml);
	}
}

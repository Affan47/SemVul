svg_post_process_href(GF_SVG_Parser *parser, XMLRI *iri)
{
	GF_Err e;

	if ( !(parser->load->flags & GF_SM_LOAD_FOR_PLAYBACK)) return;


	if ((iri->type==XMLRI_ELEMENTID) && !iri->target && iri->string) {
		gf_list_add(parser->defered_hrefs, iri);
	}
	if (iri->type != XMLRI_STRING) return;
	e = gf_node_store_embedded_data(iri, parser->load->localPath, parser->load->fileName);
	if (e) svg_report(parser, e, "Error storing embedded IRI data");
}

gf_term_resolve_xlink(GF_Node *node, char *the_url)
{
	char *url;
	GF_Scene *scene = gf_sg_get_private(gf_node_get_graph(node));
	if (!scene) return NULL;

	url = gf_strdup(the_url);

	while (node) {
		GF_FieldInfo info;
		if (gf_node_get_attribute_by_tag(node, TAG_XML_ATT_base, 0, 0, &info)==GF_OK) {
			char *new_url = gf_url_concatenate( ((XMLRI*)info.far_ptr)->string, url);
			if (new_url) {
				gf_free(url);
				url = new_url;
			}
		}
		node = gf_node_get_parent(node, 0);
	}


	if (url[0]=='#') return url;

	if (scene) {
		char *the_url;
		if (scene->redirect_xml_base) {
			the_url = gf_url_concatenate(scene->redirect_xml_base, url);
		} else {


			the_url = gf_strdup(url);
		}
		gf_free(url);
		return the_url;
	}
	return url;
}

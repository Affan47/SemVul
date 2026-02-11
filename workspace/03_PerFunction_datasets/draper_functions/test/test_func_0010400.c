gf_smil_setup_events(GF_Node *node)
{
	GF_FieldInfo info;
	if (gf_node_get_attribute_by_tag(node, TAG_SVG_ATT_begin, 0, 0, &info) == GF_OK)
		gf_smil_setup_event_list(node, * (GF_List **)info.far_ptr, 1);
	if (gf_node_get_attribute_by_tag(node, TAG_SVG_ATT_end, 0, 0, &info) == GF_OK)
		gf_smil_setup_event_list(node, * (GF_List **)info.far_ptr, 0);
}

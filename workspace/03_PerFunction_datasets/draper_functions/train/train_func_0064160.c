gf_dom_add_text_node(GF_Node *parent, char *text_data)
{
	GF_DOMText *text;
	GF_SAFEALLOC(text, GF_DOMText);

	gf_node_setup((GF_Node *)text, TAG_DOMText);
	text->sgprivate->scenegraph = parent->sgprivate->scenegraph;
	text->textContent = text_data;
	gf_node_register((GF_Node *)text, parent);
	gf_node_list_add_child_last(&((GF_ParentNode *)parent)->children, (GF_Node*)text, NULL);
	return text;
}

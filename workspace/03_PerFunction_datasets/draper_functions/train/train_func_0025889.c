gf_dom_set_textContent(GF_Node *n, char *text)
{
	GF_ParentNode *par = (GF_ParentNode *)n;
	gf_node_unregister_children(n, par->children);
	par->children = NULL;
	if (text) gf_dom_add_text_node(n, gf_strdup( text) );
}

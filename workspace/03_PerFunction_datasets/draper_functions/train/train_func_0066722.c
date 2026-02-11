grecs_node_free(struct grecs_node *node)
{
	if (!node)
		return;
	switch (node->type) {
	case grecs_node_root:
		grecs_symtab_free(node->v.texttab);
		break;
	default:
		grecs_value_free(node->v.value);
	}
	grecs_free(node->ident);
	grecs_free(node);
}

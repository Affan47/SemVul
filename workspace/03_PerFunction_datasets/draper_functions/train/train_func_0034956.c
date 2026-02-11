svg_traverse_title(GF_Node *node, void *rs, Bool is_destroy)
{
	GF_Scene *scene = (GF_Scene *)gf_node_get_private(node);
	scene->world_info = is_destroy ? NULL : node;
}

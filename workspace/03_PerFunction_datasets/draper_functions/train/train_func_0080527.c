gf_node_animation_get(GF_Node *node, u32 i)
{
	if (!node || !node->sgprivate->interact || !node->sgprivate->interact->animations) return 0;
	return gf_list_get(node->sgprivate->interact->animations, i);
}

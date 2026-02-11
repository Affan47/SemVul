apol_infoflow_node_compare(const void *a, const void *b __attribute__ ((unused)), void *data)
{
	apol_infoflow_node_t *node = (apol_infoflow_node_t *) a;
	struct apol_infoflow_node_key *key = (struct apol_infoflow_node_key *)data;
	if (node->type != key->type) {
		return (int)((char *)node->type - (char *)key->type);
	}
	return node->node_type - key->node_type;
}

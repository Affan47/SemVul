ucfg_lookup_string(ucfg_node *root, const char *path)
{
	ucfg_node *hit;
	int result = ucfg_lookup(root, &hit, path);
	if (result != UCFG_OK)
		return NULL;
	return hit->value;
}

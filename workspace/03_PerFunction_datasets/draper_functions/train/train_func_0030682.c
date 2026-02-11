amp_node_get_property_from_token (AnjutaProjectNode *node, gint token, gint pos)
{
	GList *item;

	for (item = anjuta_project_node_get_properties_info (node); item != NULL; item = g_list_next (item))
	{
		AmpPropertyInfo *info = (AmpPropertyInfo *)item->data;

		if ((info->token_type == token) && (info->position == pos))
		{
			return anjuta_project_node_get_property (node, info->base.id);
		}
	}

	return NULL;
}

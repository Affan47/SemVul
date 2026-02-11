move_map_elements (ETreeTableAdapter *etta,
                   gint to,
                   gint from,
                   gint count)
{
	if (count <= 0 || from >= etta->priv->n_map)
		return;
	memmove (etta->priv->map_table + to, etta->priv->map_table + from, count * sizeof (node_t *));
	etta->priv->remap_needed = TRUE;
}

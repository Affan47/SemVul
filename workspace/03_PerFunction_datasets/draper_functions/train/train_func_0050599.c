panel_toplevel_set_toplevel_id (PanelToplevel *toplevel,
				const char    *toplevel_id)
{
	g_assert (toplevel->priv->toplevel_id == NULL);

	toplevel->priv->toplevel_id = g_strdup (toplevel_id);
}

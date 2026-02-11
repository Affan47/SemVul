end_saving (GeditTab *tab)
{

	if (tab->priv->tmp_save_location)
	{
		g_object_unref (tab->priv->tmp_save_location);
		tab->priv->tmp_save_location = NULL;
	}
	tab->priv->tmp_encoding = NULL;

	install_auto_save_timeout_if_needed (tab);
}

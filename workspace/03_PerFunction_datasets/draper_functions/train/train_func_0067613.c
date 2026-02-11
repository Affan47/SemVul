gda_tree_mgr_select_dispose (GObject *object)
{
	GdaTreeMgrSelect *mgr = (GdaTreeMgrSelect *) object;

	g_return_if_fail (GDA_IS_TREE_MGR_SELECT (mgr));

	if (mgr->priv) {
		if (mgr->priv->cnc)
			g_object_unref (mgr->priv->cnc);
		if (mgr->priv->stmt)
			g_object_unref (mgr->priv->stmt);
		if (mgr->priv->params)
			g_object_unref (mgr->priv->params);
		if (mgr->priv->priv_params)
			g_object_unref (mgr->priv->priv_params);
		if (mgr->priv->non_bound_params)
			g_slist_free (mgr->priv->non_bound_params);

		g_free (mgr->priv);
		mgr->priv = NULL;
	}


	parent_class->dispose (object);
}

gda_tree_manager_dispose (GObject *object)
{
	GdaTreeManager *manager = (GdaTreeManager *) object;

	g_return_if_fail (GDA_IS_TREE_MANAGER (manager));

	if (manager->priv) {
		if (manager->priv->sub_managers) {
			g_slist_free (manager->priv->sub_managers);
			manager->priv->sub_managers = NULL;
		}
		if (manager->priv->ref_managers) {
			g_slist_foreach (manager->priv->ref_managers, (GFunc) g_object_unref, NULL);
			g_slist_free (manager->priv->ref_managers);
		}
		if (manager->priv->added_attributes) {
			GSList *list;
			for (list = manager->priv->added_attributes; list; list = list->next) {
				AddedAttribute *aa = (AddedAttribute*) list->data;
				g_free (aa->att_name);
				if (aa->value)
					gda_value_free (aa->value);
				g_free (aa);
			}
			g_slist_free (manager->priv->added_attributes);
		}
		g_free (manager->priv);
		manager->priv = NULL;
	}


	parent_class->dispose (object);
}

create_and_fill_model (struct indi_t *indi)
{
	indi_list *isl_d, *isl_p, *props;
	GtkTreeStore *treestore;
	GtkTreeIter  device, prop;
	struct prop_list_t *p;

	props = NULL;
	treestore = gtk_tree_store_new(2, G_TYPE_BOOLEAN, G_TYPE_STRING);

	for (isl_d = il_iter(indi->devices); ! il_is_last(isl_d); isl_d = il_next(isl_d)) {
		struct indi_device_t *dev = (struct indi_device_t *)il_item(isl_d);
		gtk_tree_store_append(treestore, &device, NULL);
		gtk_tree_store_set(treestore, &device,
			0, FALSE,
			1, dev->name,
			-1);
		for (isl_p = il_iter(dev->props); ! il_is_last(isl_p); isl_p = il_next(isl_p)) {
			struct indi_prop_t *iprop = (struct indi_prop_t *)il_item(isl_p);
			gtk_tree_store_append(treestore, &prop, &device);
			gtk_tree_store_set(treestore, &prop,
				0, iprop->save,
				1, iprop->name,
				-1);
			p = g_new0(struct prop_list_t, 1);
			p->iprop = iprop;
			p->iter = prop;
			props = il_append(props, p);
		}
	}
	g_object_set_data(G_OBJECT (treestore), "prop_list", props);
	return GTK_TREE_MODEL(treestore);
}

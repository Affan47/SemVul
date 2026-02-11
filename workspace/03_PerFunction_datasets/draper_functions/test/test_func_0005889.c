gkm_gnome2_storage_constructor (GType type, guint n_props, GObjectConstructParam *props)
{
	GkmGnome2Storage *self = GKM_GNOME2_STORAGE (G_OBJECT_CLASS (gkm_gnome2_storage_parent_class)->constructor(type, n_props, props));
	CK_ATTRIBUTE attr;

	g_return_val_if_fail (self, NULL);

	g_return_val_if_fail (self->directory, NULL);
	self->filename = g_build_filename (self->directory, "user.keystore", NULL);

	g_return_val_if_fail (self->manager, NULL);
	g_return_val_if_fail (self->module, NULL);


	attr.type = CKA_LABEL;
	attr.pValue = "";
	attr.ulValueLen = 0;

	gkm_store_register_schema (GKM_STORE (self), &attr, NULL, 0);

	return G_OBJECT (self);
}

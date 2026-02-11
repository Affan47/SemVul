gkm_gnome2_file_finalize (GObject *obj)
{
	GkmGnome2File *self = GKM_GNOME2_FILE (obj);

	g_assert (self->identifiers);
	g_hash_table_destroy (self->identifiers);
	self->identifiers = NULL;

	g_assert (self->checks == NULL);

	g_assert (self->publics);
	g_hash_table_destroy (self->publics);
	self->publics = NULL;

	if (self->privates)
		g_hash_table_destroy (self->privates);
	self->privates = NULL;

	free_unknown_block_list (self->unknowns);
	self->unknowns = NULL;

	G_OBJECT_CLASS (gkm_gnome2_file_parent_class)->finalize (obj);
}

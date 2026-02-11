brasero_caps_data_new (BraseroImageFS fs_type)
{
	GSList *iter;
	GSList *retval = NULL;
	BraseroBurnCaps *self;
	GSList *encompassing = NULL;
	gboolean have_the_one = FALSE;

	BRASERO_BURN_LOG_WITH_FULL_TYPE (BRASERO_TRACK_TYPE_DATA,
					 fs_type,
					 BRASERO_PLUGIN_IO_NONE,
					 "New caps required");

	self = brasero_burn_caps_get_default ();

	for (iter = self->priv->caps_list; iter; iter = iter->next) {
		BraseroCaps *caps;
		BraseroImageFS common;

		caps = iter->data;

		if (caps->type.type != BRASERO_TRACK_TYPE_DATA)
			continue;

		if (caps->type.subtype.fs_type == fs_type) {

			have_the_one = TRUE;
			retval = g_slist_prepend (retval, caps);
			continue;
		}


		common = caps->type.subtype.fs_type & fs_type;
		if (common == BRASERO_IMAGE_FS_NONE)
			continue;


		if (caps->type.subtype.fs_type == common)
			retval = g_slist_prepend (retval, caps);


		if (fs_type == common)
			encompassing = g_slist_prepend (encompassing, caps);
	}

	if (!have_the_one) {
		BraseroCaps *caps;

		caps = g_new0 (BraseroCaps, 1);
		caps->flags = BRASERO_PLUGIN_IO_ACCEPT_FILE;
		caps->type.type = BRASERO_TRACK_TYPE_DATA;
		caps->type.subtype.fs_type = fs_type;

		if (encompassing) {
			for (iter = encompassing; iter; iter = iter->next) {
				BraseroCaps *iter_caps;

				iter_caps = iter->data;
				brasero_caps_copy_deep (self, caps, iter_caps);
			}
		}

		self->priv->caps_list = g_slist_insert_sorted (self->priv->caps_list,
							       caps,
							       brasero_burn_caps_sort);
		retval = g_slist_prepend (retval, caps);
	}

	g_slist_free (encompassing);

	g_object_unref (self);

	return retval;
}

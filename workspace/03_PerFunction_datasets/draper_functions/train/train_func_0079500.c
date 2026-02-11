brasero_plugin_can_burn (BraseroPlugin *plugin)
{
	GSList *iter;
	BraseroBurnCaps *self;

	self = brasero_burn_caps_get_default ();

	for (iter = self->priv->caps_list; iter; iter = iter->next) {
		BraseroCaps *caps;
		GSList *links;

		caps = iter->data;
		if (caps->type.type != BRASERO_TRACK_TYPE_DISC)
			continue;

		for (links = caps->links; links; links = links->next) {
			BraseroCapsLink *link;
			GSList *plugins;

			link = links->data;


			for (plugins = link->plugins; plugins; plugins = plugins->next) {
				BraseroPlugin *tmp;

				tmp = plugins->data;
				if (tmp == plugin) {
					g_object_unref (self);
					return BRASERO_BURN_OK;
				}
			}
		}
	}

	g_object_unref (self);
	return BRASERO_BURN_NOT_SUPPORTED;
}

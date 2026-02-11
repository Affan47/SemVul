gitg_changed_file_set_property(GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec)
{
	GitgChangedFile *self = GITG_CHANGED_FILE(object);

	switch (prop_id)
	{
		case PROP_FILE:
			self->priv->file = g_value_dup_object(value);
		break;
		case PROP_STATUS:
			self->priv->status = g_value_get_enum(value);
			update_monitor(self);
		break;
		case PROP_CHANGES:
			self->priv->changes = g_value_get_flags(value);
			update_monitor(self);
		break;
		case PROP_SHA:
			set_sha_real(self, g_value_get_string(value));
		break;
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}

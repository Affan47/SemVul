gitg_command_set_property (GObject      *object,
                           guint         prop_id,
                           const GValue *value,
                           GParamSpec   *pspec)
{
	GitgCommand *self = GITG_COMMAND (object);

	switch (prop_id)
	{
		case PROP_REPOSITORY:
			self->priv->repository = g_value_dup_object (value);
			break;
		case PROP_ARGUMENTS:
			gitg_command_set_argumentsv (self,
			                             g_value_get_boxed (value));
			break;
		case PROP_ENVIRONMENT:
			gitg_command_set_environmentv (self,
			                               g_value_get_boxed (value));
			break;
		case PROP_WORKING_DIRECTORY:
			gitg_command_set_working_directory (self,
			                                    g_value_get_object (value));
			break;
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

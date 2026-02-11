__midgard_query_constraint_get_property (GObject *object, guint property_id,
		GValue *value, GParamSpec *pspec)
{
	MidgardQueryConstraint *self = (MidgardQueryConstraint *) object;

	switch (property_id) {

		case MIDGARD_QUERY_CONSTRAINT_PROPERTY:
			g_value_set_object (value, self->priv->property_value);
			break;

		case MIDGARD_QUERY_CONSTRAINT_OP:
			g_value_set_string (value, self->priv->op);
			break;

		case MIDGARD_QUERY_CONSTRAINT_HOLDER:
			g_value_set_object (value, self->priv->holder);
			break;

		case MIDGARD_QUERY_CONSTRAINT_STORAGE:
			g_value_set_object (value, self->priv->storage);
			break;

		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (self, property_id, pspec);
			break;
	}
}

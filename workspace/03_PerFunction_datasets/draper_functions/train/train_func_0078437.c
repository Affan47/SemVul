midgard_collector_add_constraint(
		MidgardCollector *self, const gchar *name,
		const gchar *op, const GValue *value)
{
	g_assert(self);
	return MIDGARD_QUERY_BUILDER_GET_CLASS(
			self->priv->builder)->add_constraint(
				self->priv->builder, name,
				op, value);
}

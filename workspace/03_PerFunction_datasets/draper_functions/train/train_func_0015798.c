_midgard_sql_query_column_dispose (GObject *object)
{
	MidgardSqlQueryColumn *self = MIDGARD_SQL_QUERY_COLUMN (object);
	if (self->query_property)
		g_object_unref (self->query_property);
	self->query_property = NULL;

	__parent_class->dispose (object);
}

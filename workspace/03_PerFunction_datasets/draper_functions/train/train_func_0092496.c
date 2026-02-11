__midgard_schema_postconfig(MidgardSchema *self)
{
	g_assert(self != NULL);


	g_hash_table_foreach (self->types, __extend_type_foreach, self);
	g_hash_table_foreach (self->types, __copy_type_foreach, self);
	g_hash_table_foreach (self->types, __initialize_paramspec, NULL);
	g_hash_table_foreach (self->types, __build_static_sql, NULL);
	g_hash_table_foreach (self->types, __validate_fields, NULL);
	__midgard_schema_register_interfaces (self);
	g_hash_table_foreach (self->types, __register_schema_type_foreach, NULL);
}

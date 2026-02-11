mono_field_static_set_value (MonoVTable *vt, MonoClassField *field, void *value)
{
	void *dest;

	g_return_if_fail (field->type->attrs & FIELD_ATTRIBUTE_STATIC);

	g_return_if_fail (!(field->type->attrs & FIELD_ATTRIBUTE_LITERAL));

	if (field->offset == -1) {

		gpointer addr;

		mono_domain_lock (vt->domain);
		addr = g_hash_table_lookup (vt->domain->special_static_fields, field);
		mono_domain_unlock (vt->domain);
		dest = mono_get_special_static_data (GPOINTER_TO_UINT (addr));
	} else {
		dest = (char*)mono_vtable_get_static_field_data (vt) + field->offset;
	}
	set_value (field->type, dest, value, FALSE);
}

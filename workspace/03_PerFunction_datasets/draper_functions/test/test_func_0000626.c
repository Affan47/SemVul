bt_struct_declaration_lookup_field_index(struct declaration_struct *struct_declaration,
				       GQuark field_name)
{
	gpointer index;
	gboolean found;

	found = g_hash_table_lookup_extended(struct_declaration->fields_by_name,
				    (gconstpointer) (unsigned long) field_name,
				    NULL, &index);
	if (!found)
		return -1;
	return (int) (unsigned long) index;
}

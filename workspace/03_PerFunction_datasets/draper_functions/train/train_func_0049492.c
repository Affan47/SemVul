add_register_value (const GDBMIValue *reg_hash, GList** list)
{
	const GDBMIValue *literal;
	const gchar *val;
	IAnjutaDebuggerRegisterData* reg;
	guint num;
	GList* prev = *list;

	literal = gdbmi_value_hash_lookup (reg_hash, "number");
	if (!literal)
		return;
	val = gdbmi_value_literal_get (literal);
	num = strtoul (val, NULL, 10);

	literal = gdbmi_value_hash_lookup (reg_hash, "value");
	if (!literal)
		return;

	reg = g_new0 (IAnjutaDebuggerRegisterData, 1);
	*list = g_list_prepend (prev, reg);
	reg->num = num;
	reg->value = (gchar *)gdbmi_value_literal_get (literal);
}

gdbmi_value_get_size (const GDBMIValue* val)
{
	g_return_val_if_fail (val != NULL, 0);

	if (val->type == GDBMI_DATA_LITERAL)
	{
		if (val->data.literal->str)
			return 1;
		else
			return 0;
	}
	else if (val->type == GDBMI_DATA_LIST)
		return g_queue_get_length (val->data.list);
	else if (val->type == GDBMI_DATA_HASH)
		return g_hash_table_size (val->data.hash);
	else
		return 0;
}

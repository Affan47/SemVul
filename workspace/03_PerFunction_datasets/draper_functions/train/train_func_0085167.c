_nm_utils_convert_op_array_to_string (const GValue *src_value, GValue *dest_value)
{
	const GPtrArray *strings;

	g_return_if_fail (g_type_is_a (G_VALUE_TYPE (src_value), DBUS_TYPE_G_ARRAY_OF_OBJECT_PATH));

	strings = (const GPtrArray *) g_value_get_boxed (src_value);
	_string_array_to_string (strings, dest_value);
}

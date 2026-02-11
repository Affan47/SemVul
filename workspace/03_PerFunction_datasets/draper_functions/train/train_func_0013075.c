nemo_file_info_get_string_attribute (NemoFileInfo *file,
					 const char *attribute_name)
{
	g_return_val_if_fail (NEMO_IS_FILE_INFO (file), NULL);
	g_return_val_if_fail (NEMO_FILE_INFO_GET_IFACE (file)->get_string_attribute != NULL, NULL);
	g_return_val_if_fail (attribute_name != NULL, NULL);

	return NEMO_FILE_INFO_GET_IFACE (file)->get_string_attribute
		(file, attribute_name);
}

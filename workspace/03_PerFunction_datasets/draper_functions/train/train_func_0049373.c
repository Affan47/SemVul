nautilus_file_is_broken_symbolic_link (NautilusFile *file)
{
	if (file == NULL) {
		return FALSE;
	}

	g_return_val_if_fail (NAUTILUS_IS_FILE (file), FALSE);


	return nautilus_file_get_file_type (file) == G_FILE_TYPE_SYMBOLIC_LINK;
}

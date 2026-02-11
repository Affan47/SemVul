nautilus_file_check_if_ready (NautilusFile *file,
			      NautilusFileAttributes file_attributes)
{


	if (file == NULL) {
		return TRUE;
	}

	g_return_val_if_fail (NAUTILUS_IS_FILE (file), FALSE);

	return NAUTILUS_FILE_CLASS (G_OBJECT_GET_CLASS (file))->check_if_ready (file, file_attributes);
}

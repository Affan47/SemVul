nautilus_file_is_executable (NautilusFile *file)
{
	if (!file->details->has_permissions) {


		return FALSE;
	}

	return file->details->can_execute;
}

nemo_directory_is_desktop_directory (NemoDirectory   *directory)
{
	if (directory->details->location == NULL) {
		return FALSE;
	}

	return nemo_is_desktop_directory (directory->details->location);
}

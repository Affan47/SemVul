get_preferred_archive_for_mime_type (const char    *mime_type,
				     FrArchiveCaps  requested_capabilities)
{
	int i;

	for (i = 0; i < Registered_Archives->len; i++) {
		FrRegisteredArchive *archive;
		FrArchiveCaps        capabilities;

		archive = g_ptr_array_index (Registered_Archives, i);
		capabilities = fr_registered_archive_get_potential_capabilities (archive, mime_type);


		if (((capabilities ^ requested_capabilities) & requested_capabilities) == 0)
			return archive->type;
	}

	return 0;
}

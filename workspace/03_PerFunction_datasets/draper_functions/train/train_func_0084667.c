fr_archive_create (GFile      *file,
		   const char *mime_type)
{
	FrArchiveCaps  requested_capabilities;
	GType          archive_type;
	FrArchive     *archive;
	GFile         *parent;

	if (mime_type == NULL)
		mime_type = _g_mime_type_get_from_filename (file);


	requested_capabilities = FR_ARCHIVE_CAN_READ_WRITE;
	archive_type = get_archive_type_from_mime_type (mime_type, requested_capabilities);


	if (archive_type == 0) {
		requested_capabilities ^= FR_ARCHIVE_CAN_READ;
		archive_type = get_archive_type_from_mime_type (mime_type, requested_capabilities);
	}

	archive = create_archive_for_mime_type (archive_type,
						file,
						mime_type,
						FR_ARCHIVE_CAN_WRITE);

	parent = g_file_get_parent (file);
	archive->priv->have_write_permissions = _g_file_check_permissions (parent, W_OK);
	archive->read_only = ! fr_archive_is_capable_of (archive, FR_ARCHIVE_CAN_WRITE) || ! archive->priv->have_write_permissions;

	g_object_unref (parent);

	return archive;
}

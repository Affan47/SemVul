get_destination_for_uri (DirectoryCopyData *dcd,
		         GFile             *file)
{
	GFile *destination_file;
	char  *relative_path;

	relative_path = g_file_get_relative_path (dcd->source, file);
	if (relative_path != NULL)
		destination_file = g_file_resolve_relative_path (dcd->destination, relative_path);
	else
		destination_file = g_file_dup (dcd->destination);

	g_free (relative_path);

	return destination_file;
}

fr_command_lha_extract (FrCommand  *comm,
			const char *from_file,
			GList      *file_list,
			const char *dest_dir,
			gboolean    overwrite,
			gboolean    skip_older,
			gboolean    junk_paths)
{
	GList *scan;
	char   options[5];
	int    i = 0;

	fr_process_begin_command (comm->process, "lha");

	if (dest_dir != NULL)
		fr_process_set_working_dir (comm->process, dest_dir);

	options[i++] = 'x';
	options[i++] = 'f';


	if (junk_paths)
		options[i++] = 'i';

	options[i++] = 0;
	fr_process_add_arg (comm->process, options);
	fr_process_add_arg (comm->process, comm->filename);

	for (scan = file_list; scan; scan = scan->next)
		fr_process_add_arg (comm->process, scan->data);

	fr_process_end_command (comm->process);
}

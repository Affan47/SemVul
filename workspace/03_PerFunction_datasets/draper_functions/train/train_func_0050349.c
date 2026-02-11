num_files_action (GPParams *p)
{
	CameraList *list;
	int count, filecount;

	CR (gp_list_new (&list));
	CL (gp_camera_folder_list_files (p->camera, p->folder,
					 list, p->context), list);
	CL (count = gp_list_count (list), list);

	if (p->flags & FLAGS_NEW) {
		int i;
		const char *name;

		filecount = 0;
		for (i = 0; i < count; i++) {
			CameraFileInfo info;

			CL (gp_list_get_name (list, i, &name), list);
			CR (gp_camera_file_get_info (p->camera, p->folder,
						     name, &info, p->context));
			if (info.file.fields & GP_FILE_INFO_STATUS &&
			    info.file.status != GP_FILE_STATUS_DOWNLOADED)
				filecount++;
		}
	}
	else
	  filecount = count;

	gp_list_free (list);
	if (p->flags & FLAGS_QUIET)
		printf ("%i\n", filecount);
	else
		printf (_("Number of files in folder '%s': %i\n"),
			p->folder, filecount);

	return (GP_OK);
}

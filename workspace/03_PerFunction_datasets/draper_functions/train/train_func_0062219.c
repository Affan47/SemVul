delete_file_action (GPParams *p, const char *folder, const char *filename)
{
	if (p->flags & FLAGS_NEW) {
		CameraFileInfo info;

		CR (gp_camera_file_get_info (p->camera, folder, filename,
					     &info, p->context));
		if (info.file.fields & GP_FILE_INFO_STATUS &&
		    info.file.status == GP_FILE_STATUS_DOWNLOADED)
			return (GP_OK);
	}
	return (gp_camera_file_delete (p->camera, folder, filename,
				       p->context));
}

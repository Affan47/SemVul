cdda_close(input_object *obj)
{
	struct cdda_local_data *data;
	int i = 0;
#ifdef DEBUG
	alsaplayer_error("In cdda_close()\n");
#endif
	if (!obj)
		return;
	data = (struct cdda_local_data *)obj->local_data;
	if (!data) {
		return;
	}
	for (i = 0; i < MAX_TRACKS;i++) {
		if (data->tracks[i].album) {
			free(data->tracks[i].album);
		}
		if (data->tracks[i].artist) {
			free(data->tracks[i].artist);
		}
		if (data->tracks[i].track) {
			free(data->tracks[i].track);
		}
	}
	close(data->cdrom_fd);
	if (data->tl.starts) free(data->tl.starts);
	data->tl.starts = NULL;
	if (data->tl.types) free(data->tl.types);
	data->tl.types = NULL;


	if (data->tl.l_min) free(data->tl.l_min);
	data->tl.l_min = NULL;
	if (data->tl.l_sec) free(data->tl.l_sec);
	data->tl.l_sec = NULL;
	if (data->tl.l_frame) free(data->tl.l_frame);
	data->tl.l_frame = NULL;

	free(obj->local_data);
	obj->local_data = NULL;
}

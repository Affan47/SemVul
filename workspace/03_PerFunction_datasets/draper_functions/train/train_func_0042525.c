fi_gui_file_fill_status(struct fileinfo_data *file)
{
    gnet_fi_status_t status;

	g_return_if_fail(file);

    guc_fi_get_status(file->handle, &status);

	file->recv_rate = status.recv_last_rate;
	file->recv_count = status.recvcount;
	file->actively_queued = status.active_queued;
	file->passively_queued = status.passive_queued;
	file->life_count = status.lifecount;

	file->uploaded = status.uploaded;
	file->size = status.size;
	file->done = status.done;
	file->modified = status.modified;
	file->progress = file->size ? filesize_per_10000(file->size, file->done) : 0;

	file->paused = status.paused;
	file->complete = status.complete;
	file->finished = status.finished;
	file->seeding = status.seeding;
	file->dht_lookup_running = status.dht_lookup_running;
	file->dht_lookup_pending = status.dht_lookup_pending;
	file->dht_lookup_successful = 0 != status.dht_values;

	HFREE_NULL(file->status);
	file->status = h_strdup(guc_file_info_status_to_string(&status));
}

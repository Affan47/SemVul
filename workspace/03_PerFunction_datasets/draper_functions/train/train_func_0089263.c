find_dmi_entry_helper(const struct dmi_header *dh,
				  void *_data)
{
	struct find_dmi_data *data = _data;
	struct dmi_sysfs_entry *entry = data->entry;


	if (dh->type != entry->dh.type)
		return;

	if (data->instance_countdown != 0) {

		data->instance_countdown--;
		return;
	}


	data->instance_countdown--;


	data->ret = data->callback(entry, dh, data->private);
}

efi_pstore_read_func(struct efivar_entry *entry, void *data)
{
	efi_guid_t vendor = LINUX_EFI_CRASH_GUID;
	struct pstore_read_data *cb_data = data;
	char name[DUMP_NAME_LEN], data_type;
	int i;
	int cnt;
	unsigned int part;
	unsigned long time, size;

	if (efi_guidcmp(entry->var.VendorGuid, vendor))
		return 0;

	for (i = 0; i < DUMP_NAME_LEN; i++)
		name[i] = entry->var.VariableName[i];

	if (sscanf(name, "dump-type%u-%u-%d-%lu-%c",
		   cb_data->type, &part, &cnt, &time, &data_type) == 5) {
		*cb_data->id = generic_id(time, part, cnt);
		*cb_data->count = cnt;
		cb_data->timespec->tv_sec = time;
		cb_data->timespec->tv_nsec = 0;
		if (data_type == 'C')
			*cb_data->compressed = true;
		else
			*cb_data->compressed = false;
	} else if (sscanf(name, "dump-type%u-%u-%d-%lu",
		   cb_data->type, &part, &cnt, &time) == 4) {
		*cb_data->id = generic_id(time, part, cnt);
		*cb_data->count = cnt;
		cb_data->timespec->tv_sec = time;
		cb_data->timespec->tv_nsec = 0;
		*cb_data->compressed = false;
	} else if (sscanf(name, "dump-type%u-%u-%lu",
			  cb_data->type, &part, &time) == 3) {


		*cb_data->id = generic_id(time, part, 0);
		*cb_data->count = 0;
		cb_data->timespec->tv_sec = time;
		cb_data->timespec->tv_nsec = 0;
		*cb_data->compressed = false;
	} else
		return 0;

	entry->var.DataSize = 1024;
	__efivar_entry_get(entry, &entry->var.Attributes,
			   &entry->var.DataSize, entry->var.Data);
	size = entry->var.DataSize;
	memcpy(*cb_data->buf, entry->var.Data,
	       (size_t)min_t(unsigned long, EFIVARS_DATA_SIZE_MAX, size));

	return size;
}

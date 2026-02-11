get_all_license_info(char **buffer_ptr,
                     int *buffer_size,
                     uid_t uid,
                     uint16_t protocol_version)
{
	ListIterator iter;
	licenses_t *lic_entry;
	uint32_t lics_packed;
	int tmp_offset;
	Buf buffer;
	time_t now = time(NULL);

	debug2("%s: calling for all licenses", __func__);

	buffer_ptr[0] = NULL;
	*buffer_size = 0;

	buffer = init_buf(BUF_SIZE);


	lics_packed = 0;
	pack32(lics_packed, buffer);
	pack_time(now, buffer);

	slurm_mutex_lock(&license_mutex);

	if (license_list) {

		iter = list_iterator_create(license_list);
		while ((lic_entry = list_next(iter))) {


			_pack_license(lic_entry, buffer, protocol_version);
			++lics_packed;
		}
		list_iterator_destroy(iter);
	}

	slurm_mutex_unlock(&license_mutex);
	debug2("%s: processed %d licenses", __func__, lics_packed);


	tmp_offset = get_buf_offset(buffer);
	set_buf_offset(buffer, 0);
	pack32(lics_packed, buffer);
	set_buf_offset(buffer, tmp_offset);

	*buffer_size = get_buf_offset(buffer);
	buffer_ptr[0] = xfer_buf_data(buffer);
}

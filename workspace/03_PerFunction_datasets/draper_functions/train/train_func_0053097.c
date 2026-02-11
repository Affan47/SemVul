brasero_get_performance_get_buffer (BraseroGetPerformanceCDB *cdb,
				    gint sizeof_descriptors,
				    BraseroScsiGetPerfHdr *hdr,
				    BraseroScsiErrCode *error)
{
	BraseroScsiGetPerfData *buffer;
	BraseroScsiResult res;
	int request_size;
	int desc_num;


	request_size = BRASERO_GET_32 (hdr->len) +
		       G_STRUCT_OFFSET (BraseroScsiGetPerfHdr, len) +
		       sizeof (hdr->len);


	if (request_size > 2048) {
		BRASERO_MEDIA_LOG ("Oversized data (%i) setting to max (2048)", request_size);
		request_size = 2048;
	}
	else if ((request_size - sizeof (hdr)) % sizeof_descriptors) {
		BRASERO_MEDIA_LOG ("Unaligned data (%i) setting to max (2048)", request_size);
		request_size = 2048;
	}
	else if (request_size < sizeof (hdr)) {
		BRASERO_MEDIA_LOG ("Undersized data (%i) setting to max (2048)", request_size);
		request_size = 2048;
	}

	desc_num = (request_size - sizeof (BraseroScsiGetPerfHdr)) / sizeof_descriptors;


	buffer = (BraseroScsiGetPerfData *) g_new0 (uchar, request_size);

	BRASERO_SET_16 (cdb->max_desc, desc_num);
	res = brasero_scsi_command_issue_sync (cdb, buffer, request_size, error);
	if (res) {
		g_free (buffer);
		return NULL;
	}

	return buffer;
}

lha_file_header_read(LHAInputStream *stream)
{
	LHAFileHeader *header;
	int success;


	header = malloc(sizeof(LHAFileHeader) + COMMON_HEADER_LEN);

	if (header == NULL) {
		return NULL;
	}

	memset(header, 0, sizeof(LHAFileHeader));

	header->_refcount = 1;


	header->raw_data = (uint8_t *) (header + 1);
	header->raw_data_len = COMMON_HEADER_LEN;

	if (!lha_input_stream_read(stream, header->raw_data,
	                           header->raw_data_len)) {
		goto fail;
	}


	header->header_level = header->raw_data[20];

	switch (header->header_level) {
		case 0:
			success = decode_level0_header(&header, stream);
			break;

		case 1:
			success = decode_level1_header(&header, stream);
			break;

		case 2:
			success = decode_level2_header(&header, stream);
			break;

		case 3:
			success = decode_level3_header(&header, stream);
			break;

		default:
			success = 0;
			break;
	}

	if (!success) {
		goto fail;
	}


	if (strcmp(header->compress_method, LHA_COMPRESS_TYPE_DIR) != 0) {
		if (header->filename == NULL) {
			goto fail;
		}
	} else if (!strcmp(header->compress_method, LHA_COMPRESS_TYPE_DIR)
	        && (header->extra_flags & LHA_FILE_UNIX_PERMS) != 0
		&& header->filename != NULL
		&& (header->unix_perms & 0170000) == 0120000) {

		if (!parse_symlink(header)) {
			goto fail;
		}

	} else {
		if (header->path == NULL) {
			goto fail;
		}
	}


	if (header->os_type == LHA_OS_TYPE_UNKNOWN
	 || header->os_type == LHA_OS_TYPE_MSDOS
	 || header->os_type == LHA_OS_TYPE_ATARI
	 || header->os_type == LHA_OS_TYPE_OS2) {
		fix_msdos_allcaps(header);
	}


	if ((header->extra_flags & LHA_FILE_COMMON_CRC) != 0
	 && !check_common_crc(header)) {
		return 0;
	}

	return header;
fail:
	lha_file_header_free(header);
	return NULL;
}

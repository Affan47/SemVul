write_key_init(int fd, UINT32 pub_data_size, UINT32 blob_size, UINT32 vendor_data_size)
{
	UINT32 num_keys;
	BYTE version;
	int rc, offset;


	rc = lseek(fd, TSSPS_VERSION_OFFSET, SEEK_SET);
	if (rc == ((off_t) - 1)) {
		LogError("lseek: %s", strerror(errno));
		return -1;
	}


	rc = lseek(fd, TSSPS_NUM_KEYS_OFFSET, SEEK_SET);
	if (rc == ((off_t) - 1)) {
		LogError("lseek: %s", strerror(errno));
		return -1;
	}


	rc = read(fd, &num_keys, sizeof(UINT32));
	num_keys = LE_32(num_keys);
	if (rc == -1) {
		LogError("read of %zd bytes: %s", sizeof(UINT32), strerror(errno));
		return -1;
	} else if (rc == 0) {

		num_keys = 1;
		version = 1;


		rc = lseek(fd, TSSPS_VERSION_OFFSET, SEEK_SET);
		if (rc == ((off_t) - 1)) {
			LogError("lseek: %s", strerror(errno));
			return -1;
		}


		if ((rc = write_data(fd, &version, sizeof(BYTE)))) {
			LogError("%s", __FUNCTION__);
			return rc;
		}

		rc = lseek(fd, TSSPS_NUM_KEYS_OFFSET, SEEK_SET);
		if (rc == ((off_t) - 1)) {
			LogError("lseek: %s", strerror(errno));
			return -1;
		}

                num_keys = LE_32(num_keys);
		if ((rc = write_data(fd, &num_keys, sizeof(UINT32)))) {
			LogError("%s", __FUNCTION__);
			return rc;
		}


		return (TSSPS_NUM_KEYS_OFFSET + sizeof(UINT32));
	}


	offset = find_write_offset(pub_data_size, blob_size, vendor_data_size);

	if (offset != -1) {

		rc = lseek(fd, offset, SEEK_SET);
	} else {


		num_keys++;


		rc = lseek(fd, TSSPS_NUM_KEYS_OFFSET, SEEK_SET);
		if (rc == ((off_t) - 1)) {
			LogError("lseek: %s", strerror(errno));
			return -1;
		}
                num_keys = LE_32(num_keys);
		if ((rc = write_data(fd, &num_keys, sizeof(UINT32)))) {
			LogError("%s", __FUNCTION__);
			return rc;
		}

		rc = lseek(fd, 0, SEEK_END);
	}
	if (rc == ((off_t) - 1)) {
		LogError("lseek: %s", strerror(errno));
		return -1;
	}


	return rc;
}

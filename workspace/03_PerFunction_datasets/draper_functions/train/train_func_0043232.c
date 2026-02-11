istgt_lu_disk_lbread(ISTGT_LU_DISK *spec, CONN_Ptr conn, ISTGT_LU_CMD_Ptr lu_cmd, uint64_t lba, uint32_t len)
{
	uint8_t *data;
	uint64_t maxlba;
	uint64_t llen;
	uint64_t blen;
	uint64_t offset;
	uint64_t nbytes;
	int64_t rc;

	if (len == 0) {
		lu_cmd->data = NULL;
		lu_cmd->data_len = 0;
		return 0;
	}

	maxlba = spec->blockcnt;
	llen = (uint64_t) len;
	blen = spec->blocklen;
	offset = lba * blen;
	nbytes = llen * blen;

	ISTGT_TRACELOG(ISTGT_TRACE_SCSI,
	    "Read: max=%"PRIu64", lba=%"PRIu64", len=%u\n",
	    maxlba, lba, len);

	if (lba >= maxlba || llen > maxlba || lba > (maxlba - llen)) {
		ISTGT_ERRLOG("end of media\n");
		return -1;
	}

	if (nbytes > lu_cmd->iobufsize) {
		ISTGT_ERRLOG("nbytes(%u) > iobufsize(%u)\n",
		    nbytes, lu_cmd->iobufsize);
		return -1;
	}
	data = lu_cmd->iobuf;

	rc = istgt_lu_disk_seek(spec, offset);
	if (rc < 0) {
		ISTGT_ERRLOG("lu_disk_seek() failed\n");
		return -1;
	}

	rc = istgt_lu_disk_read(spec, data, nbytes);
	if (rc < 0) {
		ISTGT_ERRLOG("lu_disk_read() failed\n");
		return -1;
	}
	ISTGT_TRACELOG(ISTGT_TRACE_SCSI, "Read %"PRId64"/%"PRIu64" bytes\n",
	    rc, nbytes);

	lu_cmd->data = data;
	lu_cmd->data_len = rc;

	return 0;
}

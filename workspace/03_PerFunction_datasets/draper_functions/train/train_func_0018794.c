dtd_load_unload(int tid, uint64_t lun, int load, char *file)
{
	struct target *target;
	struct scsi_lu *lu;
	int err = TGTADM_SUCCESS;

	lu = __device_lookup(tid, lun, &target);
	if (!lu)
		return TGTADM_NO_LUN;

	if (!lu->attrs.removable)
		return TGTADM_INVALID_REQUEST;

	if (lu->path) {
		lu->bst->bs_close(lu);
		free(lu->path);
		lu->path = NULL;
	}

	lu->size = 0;
	lu->fd = 0;
	lu->dev_type_template.lu_offline(lu);

	if (load) {
		lu->path = strdup(file);
		if (!lu->path)
			return TGTADM_NOMEM;
		lu->bst->bs_open(lu, file, &lu->fd, &lu->size);
		if (lu->fd < 0) {
			free(lu->path);
			lu->path = NULL;
			return TGTADM_UNSUPPORTED_OPERATION;
		}
		lu->dev_type_template.lu_online(lu);
	}
	return err;
}

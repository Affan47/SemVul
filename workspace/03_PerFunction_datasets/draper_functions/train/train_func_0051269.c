scsi_reportluns_cdb(int report_type, int alloc_len)
{
	struct scsi_task *task;

	task = malloc(sizeof(struct scsi_task));
	if (task == NULL) {
		printf("Failed to allocate scsi task structure\n");
		return NULL;
	}

	bzero(task, sizeof(struct scsi_task));
	task->cdb[0]   = SCSI_OPCODE_REPORTLUNS;
	task->cdb[2]   = report_type;
	*(uint32_t *)&task->cdb[6] = htonl(alloc_len);

	task->cdb_size = 12;
	task->xfer_dir = SCSI_XFER_READ;
	task->expxferlen = alloc_len;

	task->params.reportluns.report_type = report_type;

	return task;
}

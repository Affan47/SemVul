qla4xxx_get_conn_event_log(struct scsi_qla_host * ha)
{
	uint32_t mbox_cmd[MBOX_REG_COUNT];
	uint32_t mbox_sts[MBOX_REG_COUNT];
	struct conn_event_log_entry *event_log = NULL;
	dma_addr_t event_log_dma = 0;
	uint32_t event_log_size = 0;
	uint32_t num_valid_entries;
	uint32_t      oldest_entry = 0;
	uint32_t	max_event_log_entries;
	uint8_t		i;

	memset(&mbox_cmd, 0, sizeof(mbox_cmd));
	memset(&mbox_sts, 0, sizeof(mbox_cmd));


	mbox_cmd[0] = MBOX_CMD_GET_CONN_EVENT_LOG;

	if (qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, 5, &mbox_cmd[0], &mbox_sts[0]) !=
	    QLA_SUCCESS)
		goto exit_get_event_log;

	event_log_size = mbox_sts[4];
	if (event_log_size == 0)
		goto exit_get_event_log;


	event_log = dma_alloc_coherent(&ha->pdev->dev, event_log_size,
				       &event_log_dma, GFP_KERNEL);
	if (event_log == NULL)
		goto exit_get_event_log;


	memset(&mbox_cmd, 0, sizeof(mbox_cmd));
	memset(&mbox_sts, 0, sizeof(mbox_cmd));

	mbox_cmd[0] = MBOX_CMD_GET_CONN_EVENT_LOG;
	mbox_cmd[2] = LSDW(event_log_dma);
	mbox_cmd[3] = MSDW(event_log_dma);

	if (qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, 5, &mbox_cmd[0], &mbox_sts[0]) !=
	    QLA_SUCCESS) {
		DEBUG2(printk("scsi%ld: %s: ERROR: Unable to retrieve event "
			      "log!\n", ha->host_no, __func__));
		goto exit_get_event_log;
	}


	num_valid_entries = mbox_sts[1];

	max_event_log_entries = event_log_size /
		sizeof(struct conn_event_log_entry);

	if (num_valid_entries > max_event_log_entries)
		oldest_entry = num_valid_entries % max_event_log_entries;

	DEBUG3(printk("scsi%ld: Connection Event Log Dump (%d entries):\n",
		      ha->host_no, num_valid_entries));

	if (ql4xextended_error_logging == 3) {
		if (oldest_entry == 0) {

			for (i=0; i < num_valid_entries; i++) {
				qla4xxx_dump_buffer((uint8_t *)event_log+
						    (i*sizeof(*event_log)),
						    sizeof(*event_log));
			}
		}
		else {


			for (i=oldest_entry; i < max_event_log_entries; i++) {
				qla4xxx_dump_buffer((uint8_t *)event_log+
						    (i*sizeof(*event_log)),
						    sizeof(*event_log));
			}
			for (i=0; i < oldest_entry; i++) {
				qla4xxx_dump_buffer((uint8_t *)event_log+
						    (i*sizeof(*event_log)),
						    sizeof(*event_log));
			}
		}
	}

exit_get_event_log:
	if (event_log)
		dma_free_coherent(&ha->pdev->dev, event_log_size, event_log,
				  event_log_dma);
}

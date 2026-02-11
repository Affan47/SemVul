tcmu_handle_completion(struct tcmu_cmd *cmd, struct tcmu_cmd_entry *entry)
{
	struct se_cmd *se_cmd = cmd->se_cmd;
	struct tcmu_dev *udev = cmd->tcmu_dev;

	if (test_bit(TCMU_CMD_BIT_EXPIRED, &cmd->flags)) {


		UPDATE_HEAD(udev->data_tail, cmd->data_length, udev->data_size);
		return;
	}

	if (entry->hdr.uflags & TCMU_UFLAG_UNKNOWN_OP) {
		UPDATE_HEAD(udev->data_tail, cmd->data_length, udev->data_size);
		pr_warn("TCMU: Userspace set UNKNOWN_OP flag on se_cmd %p\n",
			cmd->se_cmd);
		entry->rsp.scsi_status = SAM_STAT_CHECK_CONDITION;
		memcpy(se_cmd->sense_buffer, lu_comm_failure_sense,
		       sizeof(lu_comm_failure_sense));
	} else if (entry->rsp.scsi_status == SAM_STAT_CHECK_CONDITION) {
		memcpy(se_cmd->sense_buffer, entry->rsp.sense_buffer,
			       TRANSPORT_SENSE_BUFFER);

		UPDATE_HEAD(udev->data_tail, cmd->data_length, udev->data_size);
	} else if (se_cmd->se_cmd_flags & SCF_BIDI) {

		UPDATE_HEAD(udev->data_tail,
			(size_t)se_cmd->t_data_sg->length, udev->data_size);


		gather_and_free_data_area(udev,
			se_cmd->t_bidi_data_sg, se_cmd->t_bidi_data_nents);
	} else if (se_cmd->data_direction == DMA_FROM_DEVICE) {
		gather_and_free_data_area(udev,
			se_cmd->t_data_sg, se_cmd->t_data_nents);
	} else if (se_cmd->data_direction == DMA_TO_DEVICE) {
		UPDATE_HEAD(udev->data_tail, cmd->data_length, udev->data_size);
	} else if (se_cmd->data_direction != DMA_NONE) {
		pr_warn("TCMU: data direction was %d!\n",
			se_cmd->data_direction);
	}

	target_complete_cmd(cmd->se_cmd, entry->rsp.scsi_status);
	cmd->se_cmd = NULL;

	kmem_cache_free(tcmu_cmd_cache, cmd);
}

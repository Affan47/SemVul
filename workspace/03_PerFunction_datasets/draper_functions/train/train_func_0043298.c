finish_cmd(struct CommandList *c)
{
	dial_up_lockup_detection_on_fw_flash_complete(c->h, c);
	if (likely(c->cmd_type == CMD_IOACCEL1 || c->cmd_type == CMD_SCSI
			|| c->cmd_type == CMD_IOACCEL2))
		complete_scsi_command(c);
	else if (c->cmd_type == CMD_IOCTL_PEND || c->cmd_type == IOACCEL2_TMF)
		complete(c->waiting);
}

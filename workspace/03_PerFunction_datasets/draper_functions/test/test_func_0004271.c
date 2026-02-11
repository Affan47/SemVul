scsi_destroy_command_freelist(struct Scsi_Host *shost)
{


	if (!shost->cmd_pool)
		return;

	while (!list_empty(&shost->free_list)) {
		struct scsi_cmnd *cmd;

		cmd = list_entry(shost->free_list.next, struct scsi_cmnd, list);
		list_del_init(&cmd->list);
		scsi_host_free_command(shost, cmd);
	}
	shost->cmd_pool = NULL;
	scsi_put_host_cmd_pool(shost);
}

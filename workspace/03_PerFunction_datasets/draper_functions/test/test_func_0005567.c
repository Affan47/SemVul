iscsit_get_datain_req(struct iscsi_cmd *cmd)
{
	if (list_empty(&cmd->datain_list)) {
		pr_err("cmd->datain_list is empty for ITT:"
			" 0x%08x\n", cmd->init_task_tag);
		return NULL;
	}

	return list_first_entry(&cmd->datain_list, struct iscsi_datain_req,
				cmd_datain_node);
}

mgmt_ipc_cfg_initiatorname(queue_task_t *qtask)
{
	if (dconfig->initiator_name)
		strcpy(qtask->rsp.u.config.var, dconfig->initiator_name);
	mgmt_ipc_write_rsp(qtask, ISCSI_SUCCESS);
	return ISCSI_SUCCESS;
}

target_handle_task_attr(struct se_cmd *cmd)
{
	struct se_device *dev = cmd->se_dev;

	if (dev->transport->transport_flags & TRANSPORT_FLAG_PASSTHROUGH)
		return false;

	cmd->se_cmd_flags |= SCF_TASK_ATTR_SET;


	switch (cmd->sam_task_attr) {
	case TCM_HEAD_TAG:
		pr_debug("Added HEAD_OF_QUEUE for CDB: 0x%02x\n",
			 cmd->t_task_cdb[0]);
		return false;
	case TCM_ORDERED_TAG:
		atomic_inc_mb(&dev->dev_ordered_sync);

		pr_debug("Added ORDERED for CDB: 0x%02x to ordered list\n",
			 cmd->t_task_cdb[0]);


		if (!atomic_read(&dev->simple_cmds))
			return false;
		break;
	default:


		atomic_inc_mb(&dev->simple_cmds);
		break;
	}

	if (atomic_read(&dev->dev_ordered_sync) == 0)
		return false;

	spin_lock(&dev->delayed_cmd_lock);
	list_add_tail(&cmd->se_delayed_node, &dev->delayed_cmd_list);
	spin_unlock(&dev->delayed_cmd_lock);

	pr_debug("Added CDB: 0x%02x Task Attr: 0x%02x to delayed CMD listn",
		cmd->t_task_cdb[0], cmd->sam_task_attr);
	return true;
}

target_xcopy_init_pt_lun(struct se_device *se_dev,
		struct se_cmd *pt_cmd, bool remote_port)
{


	if (remote_port) {
		pr_debug("Setup emulated se_dev: %p from se_dev\n",
			pt_cmd->se_dev);
		pt_cmd->se_lun = &se_dev->xcopy_lun;
		pt_cmd->se_dev = se_dev;
	}

	pt_cmd->se_cmd_flags |= SCF_SE_LUN_CMD;
}

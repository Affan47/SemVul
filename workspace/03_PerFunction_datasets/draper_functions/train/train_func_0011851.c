lbs_allocate_cmd_buffer(struct lbs_private *priv)
{
	int ret = 0;
	u32 bufsize;
	u32 i;
	struct cmd_ctrl_node *cmdarray;

	lbs_deb_enter(LBS_DEB_HOST);


	bufsize = sizeof(struct cmd_ctrl_node) * LBS_NUM_CMD_BUFFERS;
	if (!(cmdarray = kzalloc(bufsize, GFP_KERNEL))) {
		lbs_deb_host("ALLOC_CMD_BUF: tempcmd_array is NULL\n");
		ret = -1;
		goto done;
	}
	priv->cmd_array = cmdarray;


	for (i = 0; i < LBS_NUM_CMD_BUFFERS; i++) {
		cmdarray[i].cmdbuf = kzalloc(LBS_CMD_BUFFER_SIZE, GFP_KERNEL);
		if (!cmdarray[i].cmdbuf) {
			lbs_deb_host("ALLOC_CMD_BUF: ptempvirtualaddr is NULL\n");
			ret = -1;
			goto done;
		}
	}

	for (i = 0; i < LBS_NUM_CMD_BUFFERS; i++) {
		init_waitqueue_head(&cmdarray[i].cmdwait_q);
		lbs_cleanup_and_insert_cmd(priv, &cmdarray[i]);
	}
	ret = 0;

done:
	lbs_deb_leave_args(LBS_DEB_HOST, "ret %d", ret);
	return ret;
}

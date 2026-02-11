mtip_no_dev_cleanup(struct request *rq, void *data, bool reserv)
{
	struct driver_data *dd = (struct driver_data *)data;
	struct mtip_cmd *cmd;

	if (likely(!reserv))
		blk_mq_complete_request(rq, -ENODEV);
	else if (test_bit(MTIP_PF_IC_ACTIVE_BIT, &dd->port->flags)) {

		cmd = mtip_cmd_from_tag(dd, MTIP_TAG_INTERNAL);
		if (cmd->comp_func)
			cmd->comp_func(dd->port, MTIP_TAG_INTERNAL,
					cmd, -ENODEV);
	}
}

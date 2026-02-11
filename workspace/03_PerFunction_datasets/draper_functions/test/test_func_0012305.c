ssd_end_timeout_request(struct ssd_cmd *cmd)
{
	struct ssd_device *dev = cmd->dev;
	struct ssd_rw_msg *msg = (struct ssd_rw_msg *)cmd->msg;
	int i;

	for (i=0; i<dev->nr_queue; i++) {
		disable_irq(dev->entry[i].vector);
	}

	atomic_inc(&dev->tocnt);

		hio_err("%s: cmd timeout: tag %d fun %#x\n", dev->name, msg->tag, msg->fun);
		cmd->errors = -ETIMEDOUT;
		ssd_end_request(cmd);


	for (i=0; i<dev->nr_queue; i++) {
		enable_irq(dev->entry[i].vector);
	}


	ssd_set_alarm(dev);
}

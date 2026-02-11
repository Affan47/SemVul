mei_cl_flush_queues(struct mei_cl *cl, const struct file *fp)
{
	struct mei_device *dev;

	if (WARN_ON(!cl || !cl->dev))
		return -EINVAL;

	dev = cl->dev;

	cl_dbg(dev, cl, "remove list entry belonging to cl\n");
	mei_io_list_free(&cl->dev->write_list, cl);
	mei_io_list_free(&cl->dev->write_waiting_list, cl);
	mei_io_list_flush(&cl->dev->ctrl_wr_list, cl);
	mei_io_list_flush(&cl->dev->ctrl_rd_list, cl);
	mei_io_list_flush(&cl->dev->amthif_cmd_list, cl);
	mei_io_list_flush(&cl->dev->amthif_rd_complete_list, cl);

	mei_cl_read_cb_flush(cl, fp);

	return 0;
}

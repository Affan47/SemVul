mei_cl_irq_connect(struct mei_cl *cl, struct mei_cl_cb *cb,
			      struct mei_cl_cb *cmpl_list)
{
	struct mei_device *dev = cl->dev;
	u32 msg_slots;
	int slots;
	int rets;

	msg_slots = mei_data2slots(sizeof(struct hbm_client_connect_request));
	slots = mei_hbuf_empty_slots(dev);

	if (mei_cl_is_other_connecting(cl))
		return 0;

	if (slots < msg_slots)
		return -EMSGSIZE;

	rets = mei_cl_send_connect(cl, cb);
	if (rets)
		list_move_tail(&cb->list, &cmpl_list->list);

	return rets;
}

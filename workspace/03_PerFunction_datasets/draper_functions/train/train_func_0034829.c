hsc_break_request(struct hsi_client *cl)
{
	struct hsc_client_data *cl_data = hsi_client_drvdata(cl);
	struct hsi_msg *msg;
	int ret;

	if (test_and_set_bit(HSC_RXBREAK, &cl_data->flags))
		return -EBUSY;

	msg = hsi_alloc_msg(0, GFP_KERNEL);
	if (!msg) {
		clear_bit(HSC_RXBREAK, &cl_data->flags);
		return -ENOMEM;
	}
	msg->break_frame = 1;
	msg->complete = hsc_break_received;
	msg->destructor = hsc_break_req_destructor;
	ret = hsi_async_read(cl, msg);
	if (ret < 0)
		hsc_break_req_destructor(msg);

	return ret;
}

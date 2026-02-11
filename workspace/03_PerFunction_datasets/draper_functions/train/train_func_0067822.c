smscore_gpio_get_level(struct smscore_device_t *coredev, u8 pin_num,
		u8 *level) {

	u32 total_len;
	int rc;
	void *buffer;

	struct set_gpio_msg {
		struct sms_msg_hdr x_msg_header;
		u32 msg_data[2];
	} *p_msg;


	if (pin_num > MAX_GPIO_PIN_NUMBER)
		return -EINVAL;

	total_len = sizeof(struct sms_msg_hdr) + (2 * sizeof(u32));

	buffer = kmalloc(total_len + SMS_DMA_ALIGNMENT,
			GFP_KERNEL | GFP_DMA);
	if (!buffer)
		return -ENOMEM;

	p_msg = (struct set_gpio_msg *) SMS_ALIGN_ADDRESS(buffer);

	p_msg->x_msg_header.msg_src_id = DVBT_BDA_CONTROL_MSG_ID;
	p_msg->x_msg_header.msg_dst_id = HIF_TASK;
	p_msg->x_msg_header.msg_flags = 0;
	p_msg->x_msg_header.msg_type = MSG_SMS_GPIO_GET_LEVEL_REQ;
	p_msg->x_msg_header.msg_length = (u16) total_len;
	p_msg->msg_data[0] = pin_num;
	p_msg->msg_data[1] = 0;


	rc = smscore_sendrequest_and_wait(coredev, p_msg, total_len,
			&coredev->gpio_get_level_done);

	if (rc != 0) {
		if (rc == -ETIME)
			pr_err("smscore_gpio_get_level timeout\n");
		else
			pr_err("smscore_gpio_get_level error\n");
	}
	kfree(buffer);


	*level = coredev->gpio_get_res;

	return rc;
}

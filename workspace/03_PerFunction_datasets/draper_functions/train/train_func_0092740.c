smscore_init_ir(struct smscore_device_t *coredev)
{
	int ir_io;
	int rc;
	void *buffer;

	coredev->ir.dev = NULL;
	ir_io = sms_get_board(smscore_get_board_id(coredev))->board_cfg.ir;
	if (ir_io) {
		pr_debug("IR loading\n");
		rc = sms_ir_init(coredev);

		if	(rc != 0)
			pr_err("Error initialization DTV IR sub-module\n");
		else {
			buffer = kmalloc(sizeof(struct sms_msg_data2) +
						SMS_DMA_ALIGNMENT,
						GFP_KERNEL | GFP_DMA);
			if (buffer) {
				struct sms_msg_data2 *msg =
				(struct sms_msg_data2 *)
				SMS_ALIGN_ADDRESS(buffer);

				SMS_INIT_MSG(&msg->x_msg_header,
						MSG_SMS_START_IR_REQ,
						sizeof(struct sms_msg_data2));
				msg->msg_data[0] = coredev->ir.controller;
				msg->msg_data[1] = coredev->ir.timeout;

				rc = smscore_sendrequest_and_wait(coredev, msg,
						msg->x_msg_header. msg_length,
						&coredev->ir_init_done);

				kfree(buffer);
			} else
				pr_err("Sending IR initialization message failed\n");
		}
	} else
		pr_info("IR port has not been detected\n");

	return 0;
}

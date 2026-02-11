scif_nodeqp_msg_handler(struct scif_dev *scifdev,
			struct scif_qp *qp, struct scifmsg *msg)
{
	scif_display_message(scifdev, msg, "Rcvd");

	if (msg->uop > (u32)scif_max_msg_id) {

		dev_err(&scifdev->sdev->dev,
			"Unknown message 0x%xn scifdev->node 0x%x\n",
			msg->uop, scifdev->node);
		return;
	}

	scif_intr_func[msg->uop](scifdev, msg);
}

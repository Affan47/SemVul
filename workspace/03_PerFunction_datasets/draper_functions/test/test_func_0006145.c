vivid_user_gen_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct vivid_dev *dev = container_of(ctrl->handler, struct vivid_dev, ctrl_hdl_user_gen);

	switch (ctrl->id) {
	case VIVID_CID_DISCONNECT:
		v4l2_info(&dev->v4l2_dev, "disconnect\n");
		clear_bit(V4L2_FL_REGISTERED, &dev->vid_cap_dev.flags);
		clear_bit(V4L2_FL_REGISTERED, &dev->vid_out_dev.flags);
		clear_bit(V4L2_FL_REGISTERED, &dev->vbi_cap_dev.flags);
		clear_bit(V4L2_FL_REGISTERED, &dev->vbi_out_dev.flags);
		clear_bit(V4L2_FL_REGISTERED, &dev->sdr_cap_dev.flags);
		clear_bit(V4L2_FL_REGISTERED, &dev->radio_rx_dev.flags);
		clear_bit(V4L2_FL_REGISTERED, &dev->radio_tx_dev.flags);
		break;
	case VIVID_CID_CLEAR_FB:
		vivid_clear_fb(dev);
		break;
	case VIVID_CID_BUTTON:
		dev->button_pressed = 30;
		break;
	}
	return 0;
}

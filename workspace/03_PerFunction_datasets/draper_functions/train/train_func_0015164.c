vivid_radio_tx_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct vivid_dev *dev = container_of(ctrl->handler, struct vivid_dev, ctrl_hdl_radio_tx);

	switch (ctrl->id) {
	case VIVID_CID_RADIO_TX_RDS_BLOCKIO:
		dev->radio_tx_rds_controls = ctrl->val;
		dev->radio_tx_caps &= ~V4L2_CAP_READWRITE;
		if (!dev->radio_tx_rds_controls)
			dev->radio_tx_caps |= V4L2_CAP_READWRITE;
		break;
	case V4L2_CID_RDS_TX_PTY:
		if (dev->radio_rx_rds_controls)
			v4l2_ctrl_s_ctrl(dev->radio_rx_rds_pty, ctrl->val);
		break;
	case V4L2_CID_RDS_TX_PS_NAME:
		if (dev->radio_rx_rds_controls)
			v4l2_ctrl_s_ctrl_string(dev->radio_rx_rds_psname, ctrl->p_new.p_char);
		break;
	case V4L2_CID_RDS_TX_RADIO_TEXT:
		if (dev->radio_rx_rds_controls)
			v4l2_ctrl_s_ctrl_string(dev->radio_rx_rds_radiotext, ctrl->p_new.p_char);
		break;
	case V4L2_CID_RDS_TX_TRAFFIC_ANNOUNCEMENT:
		if (dev->radio_rx_rds_controls)
			v4l2_ctrl_s_ctrl(dev->radio_rx_rds_ta, ctrl->val);
		break;
	case V4L2_CID_RDS_TX_TRAFFIC_PROGRAM:
		if (dev->radio_rx_rds_controls)
			v4l2_ctrl_s_ctrl(dev->radio_rx_rds_tp, ctrl->val);
		break;
	case V4L2_CID_RDS_TX_MUSIC_SPEECH:
		if (dev->radio_rx_rds_controls)
			v4l2_ctrl_s_ctrl(dev->radio_rx_rds_ms, ctrl->val);
		break;
	}
	return 0;
}

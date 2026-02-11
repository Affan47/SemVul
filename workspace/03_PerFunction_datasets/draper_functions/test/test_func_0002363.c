sd_stopN(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	switch (sd->bridge) {
	default:


		reg_w_riv(gspca_dev, 0x31, 0, 0);
		spca504B_WaitCmdStatus(gspca_dev);
		spca504B_PollingDataReady(gspca_dev);
		break;
	case BRIDGE_SPCA504:
	case BRIDGE_SPCA504C:
		reg_w_riv(gspca_dev, 0x00, 0x2000, 0x0000);

		if (sd->subtype == AiptekMiniPenCam13) {


			spca504A_acknowledged_command(gspca_dev, 0x24,
							0x00, 0x00, 0x9d, 1);
			spca504A_acknowledged_command(gspca_dev, 0x01,
							0x0f, 0x00, 0xff, 1);
		} else {
			spca504_acknowledged_command(gspca_dev, 0x24, 0, 0);
			reg_w_riv(gspca_dev, 0x01, 0x000f, 0x0000);
		}
		break;
	}
}

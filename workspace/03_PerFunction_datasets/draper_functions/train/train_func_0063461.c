sd_callback(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (!_OV9655_) {
		u8 state;
		u8 upsideDown;


		ctrl_in(gspca_dev, 0xc0, 2, 0x0000, 0x0000, 1, (void *)&state);


		upsideDown = (state == 0xc8 || state == 0x40);

		if (upsideDown && sd->nbRightUp > -4) {
			if (sd->nbRightUp > 0)
				sd->nbRightUp = 0;
			if (sd->nbRightUp == -3) {
				sd->mirrorMask = 1;
				sd->waitSet = 1;
			}
			sd->nbRightUp--;
		}
		if (!upsideDown && sd->nbRightUp < 4) {
			if (sd->nbRightUp  < 0)
				sd->nbRightUp = 0;
			if (sd->nbRightUp == 3) {
				sd->mirrorMask = 0;
				sd->waitSet = 1;
			}
			sd->nbRightUp++;
		}
	}

	if (sd->waitSet)
		sd->dev_camera_settings(gspca_dev);
}

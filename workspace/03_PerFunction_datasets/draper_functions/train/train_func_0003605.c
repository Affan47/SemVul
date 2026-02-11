sd_start(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int mode;
	static const struct reg_array bridge_start[NSENSORS][2] = {
	[SENSOR_OV767x] = {{bridge_start_qvga_767x,
					ARRAY_SIZE(bridge_start_qvga_767x)},
			{bridge_start_vga_767x,
					ARRAY_SIZE(bridge_start_vga_767x)}},
	[SENSOR_OV772x] = {{bridge_start_qvga_772x,
					ARRAY_SIZE(bridge_start_qvga_772x)},
			{bridge_start_vga_772x,
					ARRAY_SIZE(bridge_start_vga_772x)}},
	};
	static const struct reg_array sensor_start[NSENSORS][2] = {
	[SENSOR_OV767x] = {{sensor_start_qvga_767x,
					ARRAY_SIZE(sensor_start_qvga_767x)},
			{sensor_start_vga_767x,
					ARRAY_SIZE(sensor_start_vga_767x)}},
	[SENSOR_OV772x] = {{sensor_start_qvga_772x,
					ARRAY_SIZE(sensor_start_qvga_772x)},
			{sensor_start_vga_772x,
					ARRAY_SIZE(sensor_start_vga_772x)}},
	};


	if (sd->sensor == SENSOR_OV767x)
		sccb_reg_write(gspca_dev, 0x1e, 0x04);


	mode = gspca_dev->curr_mode;
	reg_w_array(gspca_dev, bridge_start[sd->sensor][mode].val,
				bridge_start[sd->sensor][mode].len);
	sccb_w_array(gspca_dev, sensor_start[sd->sensor][mode].val,
				sensor_start[sd->sensor][mode].len);

	set_frame_rate(gspca_dev);

	if (sd->hue)
		sethue(gspca_dev, v4l2_ctrl_g_ctrl(sd->hue));
	setsaturation(gspca_dev, v4l2_ctrl_g_ctrl(sd->saturation));
	if (sd->autogain)
		setagc(gspca_dev, v4l2_ctrl_g_ctrl(sd->autogain));
	setawb(gspca_dev, v4l2_ctrl_g_ctrl(sd->autowhitebalance));
	setaec(gspca_dev, v4l2_ctrl_g_ctrl(sd->autoexposure));
	if (sd->gain)
		setgain(gspca_dev, v4l2_ctrl_g_ctrl(sd->gain));
	setexposure(gspca_dev, v4l2_ctrl_g_ctrl(sd->exposure));
	setbrightness(gspca_dev, v4l2_ctrl_g_ctrl(sd->brightness));
	setcontrast(gspca_dev, v4l2_ctrl_g_ctrl(sd->contrast));
	if (sd->sharpness)
		setsharpness(gspca_dev, v4l2_ctrl_g_ctrl(sd->sharpness));
	sethvflip(gspca_dev, v4l2_ctrl_g_ctrl(sd->hflip),
		  v4l2_ctrl_g_ctrl(sd->vflip));
	setlightfreq(gspca_dev, v4l2_ctrl_g_ctrl(sd->plfreq));

	ov534_set_led(gspca_dev, 1);
	ov534_reg_write(gspca_dev, 0xe0, 0x00);
	return gspca_dev->usb_err;
}

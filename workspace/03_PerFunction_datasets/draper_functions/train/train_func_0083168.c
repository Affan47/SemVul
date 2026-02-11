sd_config(struct gspca_dev *gspca_dev,
		     const struct usb_device_id *id)
{
	struct sd *sd = (struct sd *) gspca_dev;
	struct cam *cam;
	int err_code;

	cam = &gspca_dev->cam;
	cam->cam_mode = vga_mode;
	cam->nmodes = ARRAY_SIZE(vga_mode);
	sd->do_lcd_stop = 0;


	err_code = zero_the_pointer(gspca_dev);
	if (err_code < 0)
		return err_code;

	err_code = stream_start(gspca_dev);
	if (err_code < 0)
		return err_code;


	err_code = cam_get_response16(gspca_dev, 0x07, 1);
	if (err_code < 0)
		return err_code;

	if (id->idProduct == 0x0110 || id->idProduct == 0x010e) {
		sd->cam_type = CAM_TYPE_CIF;
		cam->nmodes--;


		switch (gspca_dev->usb_buf[0]) {
		case 2:
			sd->sensor_type = 0;
			break;
		case 3:
			sd->sensor_type = 1;
			break;
		default:
			pr_err("Unknown CIF Sensor id : %02x\n",
			       gspca_dev->usb_buf[1]);
			return -ENODEV;
		}
		PDEBUG(D_PROBE, "MR97310A CIF camera detected, sensor: %d",
		       sd->sensor_type);
	} else {
		sd->cam_type = CAM_TYPE_VGA;


		sd->sensor_type = 1;
		sd->do_lcd_stop = 0;
		sd->adj_colors = 0;
		if (gspca_dev->usb_buf[0] == 0x01) {
			sd->sensor_type = 2;
		} else if ((gspca_dev->usb_buf[0] != 0x03) &&
					(gspca_dev->usb_buf[0] != 0x04)) {
			pr_err("Unknown VGA Sensor id Byte 0: %02x\n",
			       gspca_dev->usb_buf[0]);
			pr_err("Defaults assumed, may not work\n");
			pr_err("Please report this\n");
		}

		if ((gspca_dev->usb_buf[0] == 0x03) &&
					(gspca_dev->usb_buf[1] == 0x50))
			sd->adj_colors = 1;
		if (gspca_dev->usb_buf[0] == 0x04) {
			sd->do_lcd_stop = 1;
			switch (gspca_dev->usb_buf[1]) {
			case 0x50:
				sd->sensor_type = 0;
				PDEBUG(D_PROBE, "sensor_type corrected to 0");
				break;
			case 0x20:

				break;
			default:
				pr_err("Unknown VGA Sensor id Byte 1: %02x\n",
				       gspca_dev->usb_buf[1]);
				pr_err("Defaults assumed, may not work\n");
				pr_err("Please report this\n");
			}
		}
		PDEBUG(D_PROBE, "MR97310A VGA camera detected, sensor: %d",
		       sd->sensor_type);
	}

	sd_stopN(gspca_dev);

	if (force_sensor_type != -1) {
		sd->sensor_type = !!force_sensor_type;
		PDEBUG(D_PROBE, "Forcing sensor type to: %d",
		       sd->sensor_type);
	}

	return 0;
}

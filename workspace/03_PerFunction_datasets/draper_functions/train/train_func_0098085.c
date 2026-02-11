mt9m111_probe(struct sd *sd)
{
	u8 data[2] = {0x00, 0x00};
	int i;
	struct gspca_dev *gspca_dev = (struct gspca_dev *)sd;

	if (force_sensor) {
		if (force_sensor == MT9M111_SENSOR) {
			pr_info("Forcing a %s sensor\n", mt9m111.name);
			goto sensor_found;
		}


		return -ENODEV;
	}

	PDEBUG(D_PROBE, "Probing for a mt9m111 sensor");


	for (i = 0; i < ARRAY_SIZE(preinit_mt9m111); i++) {
		if (preinit_mt9m111[i][0] == BRIDGE) {
			m5602_write_bridge(sd,
				preinit_mt9m111[i][1],
				preinit_mt9m111[i][2]);
		} else {
			data[0] = preinit_mt9m111[i][2];
			data[1] = preinit_mt9m111[i][3];
			m5602_write_sensor(sd,
				preinit_mt9m111[i][1], data, 2);
		}
	}

	if (m5602_read_sensor(sd, MT9M111_SC_CHIPVER, data, 2))
		return -ENODEV;

	if ((data[0] == 0x14) && (data[1] == 0x3a)) {
		pr_info("Detected a mt9m111 sensor\n");
		goto sensor_found;
	}

	return -ENODEV;

sensor_found:
	sd->gspca_dev.cam.cam_mode = mt9m111_modes;
	sd->gspca_dev.cam.nmodes = ARRAY_SIZE(mt9m111_modes);

	return 0;
}

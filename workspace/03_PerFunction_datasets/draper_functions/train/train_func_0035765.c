hdcs_probe_1020(struct sd *sd)
{
	struct hdcs *hdcs;
	u16 sensor;
	int ret;

	ret = stv06xx_read_sensor(sd, HDCS_IDENT, &sensor);
	if (ret < 0 || sensor != 0x10)
		return -ENODEV;

	pr_info("HDCS-1020 sensor detected\n");

	sd->gspca_dev.cam.cam_mode = hdcs1020_mode;
	sd->gspca_dev.cam.nmodes = ARRAY_SIZE(hdcs1020_mode);

	hdcs = kmalloc(sizeof(struct hdcs), GFP_KERNEL);
	if (!hdcs)
		return -ENOMEM;


	hdcs->array.left = 24;
	hdcs->array.top  = 4;
	hdcs->array.width = HDCS_1020_DEF_WIDTH;
	hdcs->array.height = 304;
	hdcs->array.border = 4;

	hdcs->psmp = 6;

	hdcs->exp.cto = 3;
	hdcs->exp.cpo = 3;
	hdcs->exp.rs = 155;
	hdcs->exp.er = 96;

	sd->sensor_priv = hdcs;

	return 0;
}

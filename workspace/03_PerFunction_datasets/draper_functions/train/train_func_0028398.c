e2_dev_init(Epson_Device *dev, const char *devname, int conntype)
{
	DBG(5, "%s\n", __func__);

	dev->name = NULL;
	dev->model = NULL;
	dev->connection = conntype;

	dev->model_id = 0;

	dev->sane.name = devname;
	dev->sane.model = NULL;

	dev->sane.type = "flatbed scanner";
	dev->sane.vendor = "Epson";

	dev->optical_res = 0;
	dev->color_shuffle = SANE_FALSE;
	dev->extension = SANE_FALSE;
	dev->use_extension = SANE_FALSE;

	dev->need_color_reorder = SANE_FALSE;
	dev->need_double_vertical = SANE_FALSE;

	dev->cct_profile = &epson_cct_profiles[0];

	dev->cmd = &epson_cmd[EPSON_LEVEL_DEFAULT];


	if (dev->connection == SANE_EPSON_NET)
		dev->cmd = &epson_cmd[EPSON_LEVEL_B7];

	dev->last_res = 0;
	dev->last_res_preview = 0;

	dev->res_list_size = 0;
	dev->res_list = NULL;
}

qxl_send_monitors_config(struct qxl_device *qdev)
{
	int i;

	BUG_ON(!qdev->ram_header->monitors_config);

	if (qdev->monitors_config->count == 0) {
		qxl_io_log(qdev, "%s: 0 monitors??\n", __func__);
		return;
	}
	for (i = 0 ; i < qdev->monitors_config->count ; ++i) {
		struct qxl_head *head = &qdev->monitors_config->heads[i];

		if (head->y > 8192 || head->x > 8192 ||
		    head->width > 8192 || head->height > 8192) {
			DRM_ERROR("head %d wrong: %dx%d+%d+%d\n",
				  i, head->width, head->height,
				  head->x, head->y);
			return;
		}
	}
	qxl_io_monitors_config(qdev);
}

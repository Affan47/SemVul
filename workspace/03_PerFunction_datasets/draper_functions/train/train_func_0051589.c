mt9v032_update_hblank(struct mt9v032 *mt9v032)
{
	struct v4l2_rect *crop = &mt9v032->crop;
	unsigned int min_hblank = mt9v032->model->data->min_hblank;
	unsigned int hblank;

	if (mt9v032->version->version == MT9V034_CHIP_ID_REV1)
		min_hblank += (mt9v032->hratio - 1) * 10;
	min_hblank = max_t(int, mt9v032->model->data->min_row_time - crop->width,
			   min_hblank);
	hblank = max_t(unsigned int, mt9v032->hblank, min_hblank);

	return regmap_write(mt9v032->regmap, MT9V032_HORIZONTAL_BLANKING,
			    hblank);
}

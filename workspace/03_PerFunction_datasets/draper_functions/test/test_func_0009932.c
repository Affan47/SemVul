s5k6aa_set_output_framefmt(struct s5k6aa *s5k6aa,
				      struct s5k6aa_preset *preset)
{
	struct i2c_client *client = v4l2_get_subdevdata(&s5k6aa->sd);
	int fmt_index = s5k6aa_get_pixfmt_index(s5k6aa, &preset->mbus_fmt);
	int ret;

	ret = s5k6aa_write(client, REG_P_OUT_WIDTH(preset->index),
			   preset->mbus_fmt.width);
	if (!ret)
		ret = s5k6aa_write(client, REG_P_OUT_HEIGHT(preset->index),
				   preset->mbus_fmt.height);
	if (!ret)
		ret = s5k6aa_write(client, REG_P_FMT(preset->index),
				   s5k6aa_formats[fmt_index].reg_p_fmt);
	return ret;
}

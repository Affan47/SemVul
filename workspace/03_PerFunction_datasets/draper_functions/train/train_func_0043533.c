detect_pen_down(struct da9034_touch *touch, int on)
{
	if (on)
		return da903x_set_bits(touch->da9034_dev,
				DA9034_AUTO_CTRL2, DA9034_PEN_DETECT);
	else
		return da903x_clr_bits(touch->da9034_dev,
				DA9034_AUTO_CTRL2, DA9034_PEN_DETECT);
}

ltr501_calculate_lux(u16 vis_data, u16 ir_data)
{
	unsigned long ratio, lux;

	if (vis_data == 0)
		return 0;


	ratio = DIV_ROUND_UP(ir_data * 100, ir_data + vis_data);

	if (ratio < 45)
		lux = LTR501_LUX_CONV(1774, vis_data, -1105, ir_data);
	else if (ratio >= 45 && ratio < 64)
		lux = LTR501_LUX_CONV(3772, vis_data, 1336, ir_data);
	else if (ratio >= 64 && ratio < 85)
		lux = LTR501_LUX_CONV(1690, vis_data, 169, ir_data);
	else
		lux = 0;

	return lux / 1000;
}

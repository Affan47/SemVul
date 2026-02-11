fpga_switch_next(struct fpga_model* model, int y, int x,
	swidx_t last, int from_to)
{
	return fpga_switch_search(model, y, x, last,
		(last & FIRST_SW) ? 0 : last+1, from_to);
}

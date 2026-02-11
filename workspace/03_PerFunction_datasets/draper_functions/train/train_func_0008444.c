y_to_regular(struct fpga_model *model, int y)
{
	RC_CHECK(model);
	if (y < TOP_FIRST_REGULAR)
		return TOP_FIRST_REGULAR;
	if (is_aty(Y_ROW_HORIZ_AXSYMM|Y_CHIP_HORIZ_REGS, model, y))
		return y-1;
	if (y > model->y_height-BOT_LAST_REGULAR_O)
		return model->y_height-BOT_LAST_REGULAR_O;
	return y;
}

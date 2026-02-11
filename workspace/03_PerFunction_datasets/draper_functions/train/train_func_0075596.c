bufpll(struct fpga_model *model)
{
	RC_CHECK(model);
	bufpll_x(model, LEFT_IO_ROUTING);
	bufpll_x(model, model->x_width-RIGHT_IO_ROUTING_O);
	RC_RETURN(model);
}

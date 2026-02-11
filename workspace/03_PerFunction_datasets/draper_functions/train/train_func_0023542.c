find_mui_pos(struct fpga_model *model, int y)
{
	int i;
	for (i = 0; i < model->die->num_mui; i++) {
		if (y == model->die->mui_pos[i] || y == model->die->mui_pos[i]+1)
			return i;
	}
	return -1;
}

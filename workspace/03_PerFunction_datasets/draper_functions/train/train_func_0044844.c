fnet_pinw(struct fpga_model *model, net_idx_t net_i,
	int is_out, int idx)
{
	struct fpga_net *net_p;
	struct fpga_device *dev_p;
	int i, next_idx;

	if (model->rc) { HERE(); return -1; };
	net_p = fnet_get(model, net_i);
	if (!net_p) { HERE(); return -1; };

	next_idx = 0;
	for (i = 0; i < net_p->len; i++) {
		if (!(net_p->el[i].idx & NET_IDX_IS_PINW))
			continue;
		dev_p = FPGA_DEV(model, net_p->el[i].y,
			net_p->el[i].x, net_p->el[i].dev_idx);
		if ((is_out && (net_p->el[i].idx & NET_IDX_MASK) < dev_p->num_pinw_in)
		    || (!is_out && (net_p->el[i].idx & NET_IDX_MASK) >= dev_p->num_pinw_in))
			continue;
		if (next_idx == idx)
			return i;
		next_idx++;
	}
	return -1;
}

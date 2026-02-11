_fnet_remove_sw(struct fpga_model *model, struct fpga_net *net_p, int i)
{
	if (!fpga_switch_is_used(model, net_p->el[i].y, net_p->el[i].x, net_p->el[i].idx))
		HERE();
	fpga_switch_disable(model, net_p->el[i].y, net_p->el[i].x, net_p->el[i].idx);
	if (net_p->len > i+1)
		memmove(&net_p->el[i], &net_p->el[i+1],
			(net_p->len-i-1)*sizeof(net_p->el[0]));
	net_p->len--;
}

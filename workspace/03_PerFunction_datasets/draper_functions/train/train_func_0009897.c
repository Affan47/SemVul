fnet_printf(FILE* f, struct fpga_model* model, net_idx_t net_i)
{
	struct fpga_net* net;
	int i;

	net = fnet_get(model, net_i);
	if (!net) { HERE(); return; }
	for (i = 0; i < net->len; i++) {
		if (net->el[i].idx & NET_IDX_IS_PINW) {
			fprintf_inout_pin(f, model, net_i, &net->el[i]);
			continue;
		}

		fprintf(f, "net %i sw y%i x%i %s\n",
			net_i, net->el[i].y, net->el[i].x,
			fpga_switch_print(model, net->el[i].y,
				net->el[i].x, net->el[i].idx));
	}
}

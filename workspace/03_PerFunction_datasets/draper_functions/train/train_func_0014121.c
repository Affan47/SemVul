tb_sw_set_unpplugged(struct tb_switch *sw)
{
	int i;
	if (sw == sw->tb->root_switch) {
		tb_sw_WARN(sw, "cannot unplug root switch\n");
		return;
	}
	if (sw->is_unplugged) {
		tb_sw_WARN(sw, "is_unplugged already set\n");
		return;
	}
	sw->is_unplugged = true;
	for (i = 0; i <= sw->config.max_port_number; i++) {
		if (!tb_is_upstream_port(&sw->ports[i]) && sw->ports[i].remote)
			tb_sw_set_unpplugged(sw->ports[i].remote->sw);
	}
}

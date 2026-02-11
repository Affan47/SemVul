tb_switch_suspend(struct tb_switch *sw)
{
	int i, err;
	err = tb_plug_events_active(sw, false);
	if (err)
		return;

	for (i = 1; i <= sw->config.max_port_number; i++) {
		if (!tb_is_upstream_port(&sw->ports[i]) && sw->ports[i].remote)
			tb_switch_suspend(sw->ports[i].remote->sw);
	}


}

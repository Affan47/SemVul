mv88e6171_setup_global(struct dsa_switch *ds)
{
	u32 upstream_port = dsa_upstream_port(ds);
	int ret;
	u32 reg;

	ret = mv88e6xxx_setup_global(ds);
	if (ret)
		return ret;


	REG_WRITE(REG_GLOBAL, GLOBAL_CONTROL,
		  GLOBAL_CONTROL_PPU_ENABLE | GLOBAL_CONTROL_DISCARD_EXCESS);


	reg = upstream_port << GLOBAL_MONITOR_CONTROL_INGRESS_SHIFT |
		upstream_port << GLOBAL_MONITOR_CONTROL_EGRESS_SHIFT |
		upstream_port << GLOBAL_MONITOR_CONTROL_ARP_SHIFT |
		upstream_port << GLOBAL_MONITOR_CONTROL_MIRROR_SHIFT;
	REG_WRITE(REG_GLOBAL, GLOBAL_MONITOR_CONTROL, reg);


	REG_WRITE(REG_GLOBAL, GLOBAL_CONTROL_2, ds->index & 0x1f);

	return 0;
}

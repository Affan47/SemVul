mv88e6xxx_setup_common(struct dsa_switch *ds)
{
	struct mv88e6xxx_priv_state *ps = ds_to_priv(ds);

	mutex_init(&ps->smi_mutex);

	ps->id = REG_READ(REG_PORT(0), PORT_SWITCH_ID) & 0xfff0;

	INIT_WORK(&ps->bridge_work, mv88e6xxx_bridge_work);

	return 0;
}

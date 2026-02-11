mv88e6131_setup(struct dsa_switch *ds)
{
	struct mv88e6xxx_priv_state *ps = ds_to_priv(ds);
	int ret;

	ret = mv88e6xxx_setup_common(ds);
	if (ret < 0)
		return ret;

	mv88e6xxx_ppu_state_init(ds);

	switch (ps->id) {
	case PORT_SWITCH_ID_6085:
	case PORT_SWITCH_ID_6185:
		ps->num_ports = 10;
		break;
	case PORT_SWITCH_ID_6095:
		ps->num_ports = 11;
		break;
	case PORT_SWITCH_ID_6131:
	case PORT_SWITCH_ID_6131_B2:
		ps->num_ports = 8;
		break;
	default:
		return -ENODEV;
	}

	ret = mv88e6xxx_switch_reset(ds, false);
	if (ret < 0)
		return ret;

	ret = mv88e6131_setup_global(ds);
	if (ret < 0)
		return ret;

	return mv88e6xxx_setup_ports(ds);
}

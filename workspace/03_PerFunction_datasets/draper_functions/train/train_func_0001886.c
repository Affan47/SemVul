mv88e6xxx_phy_page_write(struct dsa_switch *ds, int port, int page,
			     int reg, int val)
{
	struct mv88e6xxx_priv_state *ps = ds_to_priv(ds);
	int ret;

	mutex_lock(&ps->smi_mutex);
	ret = _mv88e6xxx_phy_write_indirect(ds, port, 0x16, page);
	if (ret < 0)
		goto error;

	ret = _mv88e6xxx_phy_write_indirect(ds, port, reg, val);
error:
	_mv88e6xxx_phy_write_indirect(ds, port, 0x16, 0x0);
	mutex_unlock(&ps->smi_mutex);
	return ret;
}

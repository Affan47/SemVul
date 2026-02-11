bcm_sf2_sw_indir_rw(struct dsa_switch *ds, int op, int addr,
			       int regnum, u16 val)
{
	struct bcm_sf2_priv *priv = ds_to_priv(ds);
	int ret = 0;
	u32 reg;

	reg = reg_readl(priv, REG_SWITCH_CNTRL);
	reg |= MDIO_MASTER_SEL;
	reg_writel(priv, reg, REG_SWITCH_CNTRL);


	reg = 0x70;
	reg <<= 2;
	core_writel(priv, addr, reg);


	reg = 0x80 << 8 | regnum << 1;
	reg <<= 2;

	if (op)
		ret = core_readl(priv, reg);
	else
		core_writel(priv, val, reg);

	reg = reg_readl(priv, REG_SWITCH_CNTRL);
	reg &= ~MDIO_MASTER_SEL;
	reg_writel(priv, reg, REG_SWITCH_CNTRL);

	return ret & 0xffff;
}

ipw_set_bit(struct ipw_priv *priv, u32 reg, u32 mask)
{
	ipw_write32(priv, reg, ipw_read32(priv, reg) | mask);
}

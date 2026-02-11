plx_pci_check_sja1000(const struct sja1000_priv *priv)
{
	int flag = 0;


	if ((priv->read_reg(priv, REG_CR) & REG_CR_BASICCAN_INITIAL_MASK) ==
	    REG_CR_BASICCAN_INITIAL &&
	    (priv->read_reg(priv, SJA1000_SR) == REG_SR_BASICCAN_INITIAL) &&
	    (priv->read_reg(priv, SJA1000_IR) == REG_IR_BASICCAN_INITIAL))
		flag = 1;


	priv->write_reg(priv, SJA1000_CDR, CDR_PELICAN);


	if (priv->read_reg(priv, SJA1000_MOD) == REG_MOD_PELICAN_INITIAL &&
	    priv->read_reg(priv, SJA1000_SR) == REG_SR_PELICAN_INITIAL &&
	    priv->read_reg(priv, SJA1000_IR) == REG_IR_PELICAN_INITIAL)
		return flag;

	return 0;
}

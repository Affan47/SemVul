cs4270_reg_is_readable(struct device *dev, unsigned int reg)
{
	return (reg >= CS4270_FIRSTREG) && (reg <= CS4270_LASTREG);
}

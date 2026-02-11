fan_to_reg(int fan)
{
	return fan ? (1500000 / fan) : 0;
}

sig_i2c_bus_set_clk(struct sig_i2c_bus *b, void *s, bool val)
{
	unsigned int nr;

	nr = sig_i2c_bus_find_member(b, s);

	if (b->member[nr].clk == val) {

		return;
	}

	b->member[nr].clk = val;
	sig_i2c_bus_resolve_and(b);
}

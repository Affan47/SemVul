cobalt_i2c_exit(struct cobalt *cobalt)
{
	int i;

	cobalt_dbg(1, "i2c exit\n");

	for (i = 0; i < COBALT_NUM_ADAPTERS; i++) {
		cobalt_err("unregistered bus %s\n", cobalt->i2c_adap[i].name);
		i2c_del_adapter(&cobalt->i2c_adap[i]);
	}
}

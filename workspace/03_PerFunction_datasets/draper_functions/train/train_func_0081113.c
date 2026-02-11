free_adapters(struct i2c_adap *adapters)
{
	int i;

	for (i = 0; adapters[i].name; i++)
		free(adapters[i].name);
	free(adapters);
}

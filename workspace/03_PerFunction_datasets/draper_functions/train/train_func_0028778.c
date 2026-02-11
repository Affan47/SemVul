lookup_i2c_bus(const char *i2cbus_arg)
{
	unsigned long i2cbus;
	char *end;

	i2cbus = strtoul(i2cbus_arg, &end, 0);
	if (*end || !*i2cbus_arg) {

		return lookup_i2c_bus_by_name(i2cbus_arg);
	}
	if (i2cbus > 0xFFFFF) {
		fprintf(stderr, "Error: I2C bus out of range!\n");
		return -2;
	}

	return i2cbus;
}

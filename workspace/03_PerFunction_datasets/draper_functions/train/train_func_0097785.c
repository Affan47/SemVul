cx8800_bit_setscl(void *data, int state)
{
	struct cx88_core *core = data;

	if (state)
		core->i2c_state |= 0x02;
	else
		core->i2c_state &= ~0x02;
	cx_write(MO_I2C, core->i2c_state);
	cx_read(MO_I2C);
}

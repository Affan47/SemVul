snd_i2c_bit_hw_start(struct snd_i2c_bus *bus)
{
	if (bus->hw_ops.bit->start)
		bus->hw_ops.bit->start(bus);
}

gmux_index_wait_complete(struct apple_gmux_data *gmux_data)
{
	int i = 200;
	u8 gwr = inb(gmux_data->iostart + GMUX_PORT_WRITE);

	while (i && !(gwr & 0x01)) {
		gwr = inb(gmux_data->iostart + GMUX_PORT_WRITE);
		udelay(100);
		i--;
	}

	if (gwr & 0x01)
		inb(gmux_data->iostart + GMUX_PORT_READ);

	return !!i;
}

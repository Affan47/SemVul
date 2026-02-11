bitmap_startup_logo_incoming(int messagetype, unsigned char *message, int length, gn_data *data, struct gn_statemachine *state)
{
	nk6160_driver_instance *drvinst = NK6160_DRVINST(state) ;
	int x, i;
	unsigned char b;

	if (message[0] != 0x01 || message[1] != 0x00 || message[2] != 0x07 || message[3] != 0x08)
		return GN_ERR_UNHANDLEDFRAME;

	if (!data->bitmap || data->bitmap->type != GN_BMP_StartupLogo)
		return GN_ERR_INTERNALERROR;

	for (x = 0; x < 84; x++)
		for (b = message[5 + x], i = 0; b != 0; b >>= 1, i++)
			if (b & 0x01)
				gn_bmp_point_set(data->bitmap, x, 8 * drvinst->logoslice + i);

	return GN_ERR_NONE;
}

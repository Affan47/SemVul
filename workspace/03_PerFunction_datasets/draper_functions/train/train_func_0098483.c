gn_bmp_sms_read(int type, unsigned char *message, unsigned char *code, gn_bmp *bitmap)
{
	int offset = 0;

	bitmap->type = type;
	switch (type) {
	case GN_BMP_PictureMessage:
		offset = 2;
		break;
	case GN_BMP_OperatorLogo:
		if (!code) return GN_ERR_UNKNOWN;

		bitmap->netcode[0] = '0' + (message[0] & 0x0f);
		bitmap->netcode[1] = '0' + (message[0] >> 4);
		bitmap->netcode[2] = '0' + (message[1] & 0x0f);
		bitmap->netcode[3] = ' ';
		bitmap->netcode[4] = '0' + (message[2] & 0x0f);
		bitmap->netcode[5] = '0' + (message[2] >> 4);
		bitmap->netcode[6] = 0;

		break;
	case GN_BMP_CallerLogo:
		break;
	default:
		return GN_ERR_UNKNOWN;
	}
	bitmap->width = message[0];
	bitmap->height = message[1];

	bitmap->size = ceiling_to_octet(bitmap->width * bitmap->height);
	memcpy(bitmap->bitmap, message + offset + 2, bitmap->size);

	dprintf("Bitmap from SMS: width %i, height %i\n", bitmap->width, bitmap->height);

	return GN_ERR_NONE;
}

file_nol_save(FILE *file, gn_bmp *bitmap, gn_phone *info)
{

	char header[] = {'N','O','L',0x00,0x01,0x00,
		         0x00,0x00,
		         0x00,0x00,
		         0x00,0x00,
		         0x00,0x00,
		         0x01,0x00,0x01,0x00,
		         0x00,

		         0x00};
	char buffer[8];
	int i, j, country, net;

	gn_bmp_resize(bitmap, GN_BMP_OperatorLogo, info);

	sscanf(bitmap->netcode, "%d %d", &country, &net);

	header[6] = country % 256;
	header[7] = country / 256;
	header[8] = net % 256;
	header[9] = net / 256;
	header[10] = bitmap->width;
	header[12] = bitmap->height;

	fwrite(header, 1, sizeof(header), file);

	for (i = 0; i < bitmap->size; i++) {
		for (j = 7; j >= 0; j--)
			if ((bitmap->bitmap[i] & (1 << j)) > 0) {
				buffer[7-j] = '1';
			} else {
				buffer[7-j] = '0';
			}
		fwrite(buffer, 1, 8, file);
	}
}

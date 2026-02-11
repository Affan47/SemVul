SDLVid_LoadCursor(char *maskdata)
{
	s32 ind, i, j;
	u8 data[4*32];
	u8 mask[4*32];

	ind = -1;
	for (i=0; i<32; i++) {
		for (j=0; j<32; j++) {
			if (j%8) {
				data[ind] <<= 1;
				mask[ind] <<= 1;
			} else {
				ind++;
				data[ind] = mask[ind] = 0;
			}
			switch (maskdata[j+32*i]) {

			case 1:
				data[ind] |= 0x01;

			case 2:
				mask[ind] |= 0x01;
				break;
			}
		}
	}
	return SDL_CreateCursor(data, mask, 32, 32, 0, 0);
}

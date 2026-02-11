adv_bignum_write_num(Driver * drvthis, char num_map[][4][3], int x, int num, int height, int offset)
{
	int y, dx;

	for (y = 0; y < height; y++) {
		if (num == 10) {
			unsigned char c = num_map[num][y][0];


			if (c < ' ')
				c += offset;

			drvthis->chr(drvthis, x, y + 1, c);
		}
		else {
			for (dx = 0; dx < 3; dx++) {
				unsigned char c = num_map[num][y][dx];


				if (c < ' ')
					c += offset;

				drvthis->chr(drvthis, x + dx, y + 1, c);
			}
		}
	}
}

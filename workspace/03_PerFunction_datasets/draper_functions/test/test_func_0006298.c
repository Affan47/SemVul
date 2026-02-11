fill_static(int black, int gray, int white)
{
	unsigned char *p = bits;
	for (int i = width*height; i > 0; --i) {
		switch (std::rand()%5) {
			case 0: case 1: *p++ = black; break;
			case 2: case 3: *p++ = gray; break;
			case 4: *p++ = white; break;
		}
	}
}

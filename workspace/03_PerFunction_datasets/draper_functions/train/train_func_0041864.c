prepare_glyphs(void)
{
	int c;

	for (c = 0; c < nglyphs; c++) {
		unsigned int x;
		unsigned int y;
		unsigned short xmin, ymin, xmax, ymax;


		if (!(is_readable_glyph(glyph[c].ord))) {
			continue;
		}

		xmin=0;
		ymin=0;
		xmax=glyph[c].width-1;
		ymax=glyph[c].height-1;


		for (y=0; y<glyph[c].height; ++y) {
			unsigned char empty;
			empty=1;

			for (x=0; x<glyph[c].width; ++x) {
				if (glyph[c].pattern[x][y]) {
					empty=0;
					break;
				}
			}

			if (empty) {
				ymin++;
			} else {
				break;
			}

		}


		for (y=glyph[c].height-1; y>ymin; --y) {
			unsigned char empty;
			empty=1;

			for (x=0; x<glyph[c].width; ++x) {
				if (glyph[c].pattern[x][y]) {
					empty=0;
					break;
				}
			}

			if (empty) {
				ymax--;
			} else {
				break;
			}

		}


		for (x=0; x<glyph[c].width; ++x) {
			unsigned char empty;
			empty=1;

			for (y=ymin; y<=ymax; ++y) {
				if (glyph[c].pattern[x][y]) {
					empty=0;
					break;
				}
			}

			if (empty) {
				xmin++;
			} else {
				break;
			}

		}


		for (x=xmax; x>xmin; --x) {
			unsigned char empty;
			empty=1;

			for (y=ymin; y<=ymax; ++y) {
				if (glyph[c].pattern[x][y]) {
					empty=0;
					break;
				}
			}

			if (empty) {
				xmax--;
			} else {
				break;
			}

		}

		glyph[c].xmin=xmin;
		glyph[c].xmax=xmax;
		glyph[c].ymin=ymin;
		glyph[c].ymax=ymax;
	}
}

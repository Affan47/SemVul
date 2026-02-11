lis2_HD44780_senddata(PrivateData *p, unsigned char displayID, unsigned char flags, unsigned char ch)
{
static int mode = 0;
static unsigned char charNum = 0;
static unsigned char rowNum = 0;

	if (flags == RS_DATA) {
		if (mode == SETCHAR) {
			if (p->connectiontype == HD44780_CT_LIS2) {
				if (rowNum < p->cellheight)

					setLIS2CustomCharRow(p->fd, charNum, rowNum, ch);
				else
					mode = 0;
			}


			rowNum++;

			if (p->connectiontype == HD44780_CT_MPLAY) {
				if (rowNum == p->cellheight) {

					setMPlayCustomChars(p->fd, p->cc);

					p->hd44780_functions->uPause(p, 40);

					mode = 0;
				}
			}
		}
		else {
			if (p->connectiontype == HD44780_CT_LIS2) {


				if (ch < 7)
					ch++;
			}
			else {


				if (ch < NUM_CCs)
					ch += NUM_CCs;
			}


			write(p->fd, &ch, 1);
		}
	}
	else {
		if ((ch & POSITION) != 0) {
			unsigned char divisor = (p->ext_mode) ? 0x20 : 0x40;


			ch &= ~POSITION;


			gotoXY(p->fd, ch % divisor, ch / divisor);
		}
		else if ((ch & SETCHAR) != 0) {
			mode = SETCHAR;

			if (p->connectiontype == HD44780_CT_LIS2) {

				charNum = (ch & ~SETCHAR) / 8;


				charNum++;


				if (charNum == 8)
					charNum = 7;
			}


			rowNum = 0;
		}
	 	else

			write(p->fd, &ch, 1);
	}
}

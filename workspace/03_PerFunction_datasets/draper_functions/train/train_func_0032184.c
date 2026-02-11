remove_iacs(struct tsession *ts, int *pnum_totty)
{
	unsigned char *ptr0 = TS_BUF1(ts) + ts->wridx1;
	unsigned char *ptr = ptr0;
	unsigned char *totty = ptr;
	unsigned char *end = ptr + MIN(BUFSIZE - ts->wridx1, ts->size1);
	int num_totty;

	while (ptr < end) {
		if (*ptr != IAC) {
			char c = *ptr;

			*totty++ = c;
			ptr++;


			if (c == '\r' && ptr < end && (*ptr == '\n' || *ptr == '\0'))
				ptr++;
			continue;
		}

		if ((ptr+1) >= end)
			break;
		if (ptr[1] == NOP) {
			ptr += 2;
			continue;
		}
		if (ptr[1] == IAC) {
			*totty++ = ptr[1];
			ptr += 2;
			continue;
		}


		if ((ptr+2) >= end) {


			break;
		}


		if (ptr[1] == SB && ptr[2] == TELOPT_NAWS) {
			struct winsize ws;
			if ((ptr+8) >= end)
				break;
			ws.ws_col = (ptr[3] << 8) | ptr[4];
			ws.ws_row = (ptr[5] << 8) | ptr[6];
			ioctl(ts->ptyfd, TIOCSWINSZ, (char *)&ws);
			ptr += 9;
			continue;
		}

#if DEBUG
		fprintf(stderr, "Ignoring IAC %s,%s\n",
				TELCMD(ptr[1]), TELOPT(ptr[2]));
#endif
		ptr += 3;
	}

	num_totty = totty - ptr0;
	*pnum_totty = num_totty;


	if ((ptr - totty) == 0)
		return ptr0;
	ts->wridx1 += ptr - totty;
	ts->size1 -= ptr - totty;

	return memmove(ptr - num_totty, ptr0, num_totty);
}

handle_net_input(int len)
{
	int i;
	int cstart = 0;

	for (i = 0; i < len; i++) {
		byte c = G.buf[i];

		if (G.telstate == TS_NORMAL) {
			if (c == IAC) {
				cstart = i;
				G.telstate = TS_IAC;
			}
			else if (c == '\r') {
				cstart = i + 1;
				G.telstate = TS_CR;
			}


			continue;
		}

		switch (G.telstate) {
		case TS_CR:


			G.telstate = TS_COPY;
			if (c == '\0')
				break;


		case TS_COPY:

			if (c == IAC)
				G.telstate = TS_IAC;
			else
				G.buf[cstart++] = c;
			if (c == '\r')
				G.telstate = TS_CR;
			break;

		case TS_IAC:
			if (c == IAC) {
				G.buf[cstart++] = c;
				G.telstate = TS_COPY;
				break;
			}

			switch (c) {
			case SB:
				G.telstate = TS_SUB1;
				break;
			case DO:
			case DONT:
			case WILL:
			case WONT:
				G.telwish = c;
				G.telstate = TS_OPT;
				break;

			default:
				G.telstate = TS_COPY;
			}
			break;

		case TS_OPT:
			telopt(c);
			G.telstate = TS_COPY;
			break;

		case TS_SUB1:
		case TS_SUB2:
			subneg(c);
			break;
		}
	}

	if (G.telstate != TS_NORMAL) {

		if (G.iaclen)
			iac_flush();
		if (G.telstate == TS_COPY)
			G.telstate = TS_NORMAL;
		len = cstart;
	}

	if (len)
		full_write(STDOUT_FILENO, G.buf, len);
}

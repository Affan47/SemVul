lexGetQuotedPrintable()
    {
    char cur;

    lexClearToken();
    do {
	cur = lexGetc();
	switch (cur) {
	    case '=': {
		int c = 0;
		int next[2];
		int i;
		for (i = 0; i < 2; i++) {
		    next[i] = lexGetc();
		    if (next[i] >= '0' && next[i] <= '9')
			c = c * 16 + next[i] - '0';
		    else if (next[i] >= 'A' && next[i] <= 'F')
			c = c * 16 + next[i] - 'A' + 10;
		    else
			break;
		    }
		if (i == 0) {

		    if (next[0] == '\n') {
			++mime_lineNum;
			}
		    else {
			lexPushLookaheadc('=');
			goto EndString;
			}
		    }
		else if (i == 1) {
		    lexPushLookaheadc(next[1]);
		    lexPushLookaheadc(next[0]);
		    lexAppendc('=');
		} else {
		    lexAppendc(c);
		    }
		break;
		}
	    case '\n': {
		lexPushLookaheadc('\n');
		goto EndString;
		}
	    case (char)EOF:
		break;
	    default:
		lexAppendc(cur);
		break;
	    }
	} while (cur != (char)EOF);

EndString:
    lexAppendc(0);
    return lexStr();
    }

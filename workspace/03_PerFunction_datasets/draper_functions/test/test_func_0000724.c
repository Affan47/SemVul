colcrt(FILE *f) {
	wint_t c;
	wchar_t *cp, *dp;
	int i, w;

	for (;;) {
		c = getwc(f);
		if (c == WEOF) {
			pflush(outline);
			fflush(stdout);
			break;
		}
		switch (c) {
		case '\n':
			if (outline >= 265)
				pflush(62);
			outline += 2;
			outcol = 0;
			continue;
		case '\016':
		case '\017':
			continue;
		case 033:
			c = getwc(f);
			switch (c) {
			case '9':
				if (outline >= 266)
					pflush(62);
				outline++;
				continue;
			case '8':
				if (outline >= 1)
					outline--;
				continue;
			case '7':
				outline -= 2;
				if (outline < 0)
					outline = 0;
				continue;
			default:
				continue;
			}
		case '\b':
			if (outcol)
				outcol--;
			continue;
		case '\t':
			outcol += 8;
			outcol &= ~7;
			outcol--;
			c = ' ';
		default:
			w = wcwidth(c);
			if (outcol + w > 132) {
				outcol++;
				continue;
			}
			cp = &page[outline][outcol];
			outcol += w;
			if (c == '_') {
				if (suppresul)
					continue;
				cp += 132;
				c = '-';
			}
			if (*cp == 0) {

				for (i = 0; i < w; i++)
					cp[i] = c;
				dp = cp - (outcol - w);
				for (cp--; cp >= dp && *cp == 0; cp--)
					*cp = ' ';
			} else {
				if (plus(c, *cp) || plus(*cp, c))
					*cp = '+';
				else if (*cp == ' ' || *cp == 0) {
					for (i = 1; i < w; i++)
						if (cp[i] != ' ' && cp[i] != 0)
							continue;
					for (i = 0; i < w; i++)
						cp[i] = c;
				}
			}
			continue;
		}
	}
}

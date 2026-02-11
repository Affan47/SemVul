_php_math_number_format(double d, int dec, char dec_point, char thousand_sep)
{
	char *tmpbuf = NULL, *resbuf;
	char *s, *t;
	char *dp;
	int integral;
	int tmplen, reslen=0;
	int count=0;
	int is_negative=0;

	if (d < 0) {
		is_negative = 1;
		d = -d;
	}

	dec = MAX(0, dec);
	d = _php_math_round(d, dec, PHP_ROUND_HALF_UP);

	tmplen = spprintf(&tmpbuf, 0, "%.*F", dec, d);

	if (tmpbuf == NULL || !isdigit((int)tmpbuf[0])) {
		return tmpbuf;
	}


	if (dec) {
		dp = strpbrk(tmpbuf, ".,");
	} else {
		dp = NULL;
	}


	if (dp) {
		integral = dp - tmpbuf;
	} else {

		integral = tmplen;
	}


	if (thousand_sep) {
		integral += (integral-1) / 3;
	}

	reslen = integral;

	if (dec) {
		reslen += dec;

		if (dec_point) {
			reslen++;
		}
	}


	if (is_negative) {
		reslen++;
	}
	resbuf = (char *) emalloc(reslen+1);

	s = tmpbuf+tmplen-1;
	t = resbuf+reslen;
	*t-- = '\0';


	if (dec) {
		int declen = dp ? s - dp : 0;
		int topad = dec > declen ? dec - declen : 0;


		while (topad--) {
			*t-- = '0';
		}

		if (dp) {
			s -= declen + 1;
			t -= declen;


			memcpy(t + 1, dp + 1, declen);
		}


		if (dec_point) {
			*t-- = dec_point;
		}
	}


	while(s >= tmpbuf) {
		*t-- = *s--;
		if (thousand_sep && (++count%3)==0 && s>=tmpbuf) {
			*t-- = thousand_sep;
		}
	}


	if (is_negative) {
		*t-- = '-';
	}

	efree(tmpbuf);

	return resbuf;
}

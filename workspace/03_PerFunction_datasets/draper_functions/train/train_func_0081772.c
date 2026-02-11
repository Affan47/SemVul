increment_string(zval *str)
{
	int carry=0;
	int pos=Z_STRLEN_P(str)-1;
	char *s=Z_STRVAL_P(str);
	char *t;
	int last=0;
	int ch;

	if (Z_STRLEN_P(str) == 0) {
		STR_FREE(Z_STRVAL_P(str));
		Z_STRVAL_P(str) = estrndup("1", sizeof("1")-1);
		Z_STRLEN_P(str) = 1;
		return;
	}

	while (pos >= 0) {
		ch = s[pos];
		if (ch >= 'a' && ch <= 'z') {
			if (ch == 'z') {
				s[pos] = 'a';
				carry=1;
			} else {
				s[pos]++;
				carry=0;
			}
			last=LOWER_CASE;
		} else if (ch >= 'A' && ch <= 'Z') {
			if (ch == 'Z') {
				s[pos] = 'A';
				carry=1;
			} else {
				s[pos]++;
				carry=0;
			}
			last=UPPER_CASE;
		} else if (ch >= '0' && ch <= '9') {
			if (ch == '9') {
				s[pos] = '0';
				carry=1;
			} else {
				s[pos]++;
				carry=0;
			}
			last = NUMERIC;
		} else {
			carry=0;
			break;
		}
		if (carry == 0) {
			break;
		}
		pos--;
	}

	if (carry) {
		t = (char *) emalloc(Z_STRLEN_P(str)+1+1);
		memcpy(t+1, Z_STRVAL_P(str), Z_STRLEN_P(str));
		Z_STRLEN_P(str)++;
		t[Z_STRLEN_P(str)] = '\0';
		switch (last) {
			case NUMERIC:
				t[0] = '1';
				break;
			case UPPER_CASE:
				t[0] = 'A';
				break;
			case LOWER_CASE:
				t[0] = 'a';
				break;
		}
		STR_FREE(Z_STRVAL_P(str));
		Z_STRVAL_P(str) = t;
	}
}

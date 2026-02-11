hexToChar(const String &n, bool all)
{
	if (n.length() < 2) {
		return String(n);
	}
	static char buf[2];
	unsigned int a, b;
	unsigned char c;
	a = n[0];
	b = n[1];
	if (a >= 'a' && a <= 'f') {
		a -= 87;
	}
	else if (a >= 'A' && a <= 'F') {
		a -= 55;
	}
	else if (a >= '0' && a <= '9') {
		a -= 48;
	}
	else {
		return String("%") + n;
	}
	if (b >= 'a' && b <= 'f') {
		b -= 87;
	}
	else if (b >= 'A' && b <= 'F') {
		b -= 55;
	}
	else if (b >= '0' && b <= '9') {
		b -= 48;
	}
	else {
		return String("%") + n;
	}
	c = a * 16 + b;
	if (all || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || (c == '-')) {
		buf[0] = c;
		buf[1] = '\0';
		return String(buf);
	} else {
		return String("%") + n;
	}
}

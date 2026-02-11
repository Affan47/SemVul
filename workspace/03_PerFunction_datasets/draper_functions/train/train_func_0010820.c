writestrz(const char *str)
{
	if (str) {
		writex(str, strlen(str)+1);
	} else {
		byte n = 0;
		writex(&n, 1);
	}
}

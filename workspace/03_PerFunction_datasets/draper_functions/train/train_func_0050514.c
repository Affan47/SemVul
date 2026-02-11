format_ansi(char ch) {
	if (ch == 'k')
		return ("\033[2;30m");
	if (ch == 'K')
		return ("\033[1;30m");
	if (ch == 'l')
		return ("\033[40m");
	if (ch == 'r')
		return ("\033[2;31m");
	if (ch == 'R')
		return ("\033[1;31m");
	if (ch == 's')
		return ("\033[41m");
	if (ch == 'g')
		return ("\033[2;32m");
	if (ch == 'G')
		return ("\033[1;32m");
	if (ch == 'h')
		return ("\033[42m");
	if (ch == 'y')
		return ("\033[2;33m");
	if (ch == 'Y')
		return ("\033[1;33m");
	if (ch == 'z')
		return ("\033[43m");
	if (ch == 'b')
		return ("\033[2;34m");
	if (ch == 'B')
		return ("\033[1;34m");
	if (ch == 'e')
		return ("\033[44m");
	if (ch == 'm' || ch == 'p')
		return ("\033[2;35m");
	if (ch == 'M' || ch == 'P')
		return ("\033[1;35m");
	if (ch == 'q')
		return ("\033[45m");
	if (ch == 'c')
		return ("\033[2;36m");
	if (ch == 'C')
		return ("\033[1;36m");
	if (ch == 'd')
		return ("\033[46m");
	if (ch == 'w')
		return ("\033[2;37m");
	if (ch == 'W')
		return ("\033[1;37m");
	if (ch == 'x')
		return ("\033[47m");
	if (ch == 'n')
		return ("\033[0m");
	if (ch == 'T')
		return ("\033[1m");
	if (ch == 'N')
		return ("\033[2m");
	if (ch == 'U')
		return ("\033[4m");
	if (ch == 'i')
		return ("\033[5m");
	if (ch == 'V')
		return ("\033[7m");
	if (ch == 'A')
		return ("\033(0");
	if (ch == 'a')
		return ("\033(B");

	return NULL;
}

PrintHex(const char *str)
{
	cout << setiosflags(ios::left) << setw(14 + 16 * 3 + 1) << str;
	cout << setw(0);
	str += 14;
	char *endpos = (char*) str;
	while( *endpos ) {
		long c = strtol(str, &endpos, 16);
		if( c == LONG_MIN || c == LONG_MAX )
			break;
		if( isprint(c) )
			cout << (char)c;
		else
			cout << '.';
		str = endpos;
	}
	cout << '\n';
}

skipnum(const char *s, const char *e, readui_base base) {
	for (;s<e;s++) {
		unsigned int c = (unsigned char)*s;

		if (cdigit(c)) {
			if ( c-'0' >= (base & 0xFF) &&
			    !(base & READUI_ALLOWHIGHERDIGITS) )
				break;
		} else if (c>='A' && c<='Z') {
			if (!(base & READUI_ALLOWCAPLETTERS))
				break;
			if ( c-'A'+10 >= (base & 0xFF) &&
			    !(base & READUI_ALLOWHIGHERDIGITS))
				break;
		} else if (c>='a' && c<='z') {
			if (!(base & READUI_ALLOWLCASELETTERS))
				break;
			if ( c-'a'+10 >= (base & 0xFF) &&
			    !(base & READUI_ALLOWHIGHERDIGITS))
				break;
		} else
			break;
	}

	return s;
}

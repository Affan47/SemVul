letterToCode(int letter)
{
	switch (toupper(letter)) {
		case 'A':
			return ATTR_ARCHIVE;
		case 'H':
			return ATTR_HIDDEN;
		case 'R':
			return ATTR_READONLY;
		case 'S':
			return ATTR_SYSTEM;
		default:
			usage(1);
	}
}

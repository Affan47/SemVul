hdup_convert (char *value)
{


	char *cp; long long int v = 0; long int mul = 1;
	cp = value;
	while ( *cp != (char)NULL ) {
		switch (*cp) {
			case 'k':
			case 'K':
				mul = KILOBYTE;
				*cp = '\0';
				goto end;
			case 'm':
			case 'M':
				mul = MEGABYTE;
				*cp = '\0';
				goto end;
			case 'g':
			case 'G':
				mul = GIGABYTE;
				*cp = '\0';
				goto end;
			default:
				break;
		}
		cp++;
	}
end:
	v = strtol(value, NULL, 10);
	v = v * mul;

	switch (mul) {
		case KILOBYTE:
			*cp = 'K';
			break;
		case MEGABYTE:
			*cp = 'M';
			break;
		case GIGABYTE:
			*cp = 'G';
			break;
	}
	return v;
}

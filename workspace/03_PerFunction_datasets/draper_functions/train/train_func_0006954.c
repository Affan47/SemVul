processCheckFlags(const char* flags)
{
	for (unsigned int i = 0; i < strlen(flags); i++) {
		switch (flags[i]) {
		case 'p':
			check_along_path = false;
			break;
		case 'P':
			check_along_path = true;
			break;
		case 'e':
			check_on_ellipse = false;
			break;
		case 'E':
			check_on_ellipse = true;
			break;
		case 's':
			check_along_shocks = false;
			break;
		case 'S':
			check_along_shocks = true;
			break;
		default:
			fprintf(stderr, "Unknown check type selection character <%c>, ignored.\n", flags[i]);
		}
	}
}

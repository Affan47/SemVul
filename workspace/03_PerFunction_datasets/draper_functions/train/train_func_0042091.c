scanStringForImageExtensionsSimple(char * inpt)
 {
	char *s = 0;

	s = strrchr(inpt, '.');
	if (s != 0)
	 {
	     return is_valid_suffix(++s);
	 }
	return 0;
}

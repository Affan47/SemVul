parse_boolean(bool* dst, int argc, const char** argv)
{
	if(argc > 0) {
		if(		strcmp("true", argv[0]) == 0 ||
				strcmp("yes",  argv[0]) == 0 ||
				strcmp("on",   argv[0]) == 0 ) {
			*dst = true;
			return 1;
		} else if(
				strcmp("false", argv[0]) == 0 ||
				strcmp("no",    argv[0]) == 0 ||
				strcmp("off",   argv[0]) == 0 ) {
			*dst = false;
			return 1;
		} else {
			*dst = true;
			return 0;
		}
	} else {
		*dst = true;
		return 0;
	}
}

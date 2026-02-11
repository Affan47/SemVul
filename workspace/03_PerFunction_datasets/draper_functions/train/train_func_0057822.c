buildInOut(const char* source, const char* dest, AbstractFile** in, AbstractFile** out) {
	*in = createAbstractFileFromFile(fopen(source, "rb"));
	if(!(*in)) {
		printf("cannot open source: %s\n", source);
		return FALSE;
	}

	*out = createAbstractFileFromFile(fopen(dest, "wb"));
	if(!(*out)) {
		(*in)->close(*in);
		printf("cannot open destination: %s\n", dest);
		return FALSE;
	}

	return TRUE;
}

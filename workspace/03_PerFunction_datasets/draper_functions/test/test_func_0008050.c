stream2file(FILE *in, char *file, unsigned long long int *b)
{

	FILE *handle;
	unsigned int c;
	char buf[BUFSIZE + 1];
	*b = 0;

	handle = fopen(file,"w");

	if (handle == NULL) {
		VERBOSE("%s","Could not open archive for writing");
		perror(NULL);
		return 0;
	}
	if (in == NULL) {
		VERBOSE("%s", "Could not read from stream");
		perror(NULL);
		return 0;
	}


	while(!feof(in)) {
                c = fread(buf, sizeof(char), BUFSIZE, in);
                if (fwrite(buf, sizeof(char), c, handle) != c) {
                        WARN("%s", "Writing of the archive failed");
                        perror(NULL);
                        return 1;
                }
                *b += c;
        }

	fclose(handle);
	return 0;
}

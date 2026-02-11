growable_buffer_add(char* buf, int index, char c, int* size, int* sizestep, int* maxstep) {
	if (index == *size) {

		*size += *sizestep;
		buf = realloc(buf, *size);
		if (!buf) {
			fprintf(stderr, "Couldn't allocate buffer: %i.\n", *size);
			return NULL;
		}
		if (*sizestep < *maxstep)
			*sizestep *= 2;
	}
	buf[index] = c;
	return buf;
}

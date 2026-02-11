strAddChar(string *s, char c) {
	if (s->length + 1 >= s->allocated) {
		if (DEBUG_FLAG) printf("string reallocation needed\n");
		if ((s->str = (char*) realloc(s->str, s->length + STR_ALLOC_DELTA))
			== NULL) {
			if (DEBUG_FLAG) printf("string allocation error\n");
			return STR_ERROR;
		}
		s->allocated = s->length + STR_ALLOC_DELTA;
	}
	s->str[s->length] = c;
	s->length++;
	s->str[s->length] = '\0';
	return STR_SUCCESS;
}

parsed(int tok, const char* end, const char** errPos) {
	if (errPos) *errPos = end;
	return tok;
}

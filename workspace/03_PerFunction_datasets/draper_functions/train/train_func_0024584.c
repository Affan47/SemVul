afterlastslash(const String& str) {
	size_t pos=str.strrpbrk("/\\");
	return pos!=STRING_NOT_FOUND?pos+1:0;
}

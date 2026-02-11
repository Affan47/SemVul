Extension() const {
	const char *dirEnd = strrchr(fileName.c_str(), pathSepChar);
	const char *extStart = strrchr(fileName.c_str(), '.');
	if (extStart > dirEnd)
		return extStart + 1;
	else
		return "";
}

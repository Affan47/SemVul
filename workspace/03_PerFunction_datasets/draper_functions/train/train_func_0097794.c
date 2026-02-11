filepathutil_addslash(ucs2_char_t* path)
{
	size_t length = ucs2len(path);
	if (length > 0) {
		if (path[length-1] != PATHCHAR) {

			path[length++] = PATHCHAR;
			path[length] = 0;
		}
	}
	return (path + length);
}

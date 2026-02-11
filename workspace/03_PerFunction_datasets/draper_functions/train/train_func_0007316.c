VarSuffix(const char *word, Boolean addSpace, Buffer *buf, void *dummy __unused)
{
	const char *dot;

	dot = strrchr(word, '.');
	if (dot != NULL) {
		if (addSpace) {
			Buf_AddByte(buf, (Byte)' ');
		}
		dot++;
		Buf_Append(buf, dot);
		addSpace = TRUE;
	}
	return (addSpace);
}

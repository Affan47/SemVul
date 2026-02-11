IsPhpWordStart(int ch) {
	return (IsASCII(ch) && (isalpha(ch) || (ch == '_'))) || (ch >= 0x7f);
}

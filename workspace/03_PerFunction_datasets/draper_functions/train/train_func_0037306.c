PodHeadingLevel(int pos, LexAccessor &styler) {
	int lvl = static_cast<unsigned char>(styler.SafeGetCharAt(pos + 5));
	if (lvl >= '1' && lvl <= '4') {
		return lvl - '0';
	}
	return 0;
}

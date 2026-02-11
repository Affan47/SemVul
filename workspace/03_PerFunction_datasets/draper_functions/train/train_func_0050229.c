toUTF8(string& out) const {
	out.resize(0);
	GLEStringToUTF8 conv(this);
	while (1) {
		char ch = conv.get();
		if (ch == 0) break;
		out.push_back(ch);
	}
}

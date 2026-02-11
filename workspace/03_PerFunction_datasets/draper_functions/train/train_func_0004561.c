getEmptyString() {
	static GLERC<GLEString> g_EmptyString = new GLEString();
	return g_EmptyString.get();
}

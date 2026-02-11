testMatchChars()
{
	Glob g1("a");
	assert (g1.match("a"));
	assert (!g1.match("b"));
	assert (!g1.match("aa"));
	assert (!g1.match(""));

	Glob g2("ab");
	assert (g2.match("ab"));
	assert (!g2.match("aab"));
	assert (!g2.match("abab"));
}

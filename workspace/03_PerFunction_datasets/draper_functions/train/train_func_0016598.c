testMatchQM()
{
	Glob g1("?");
	assert (g1.match("a"));
	assert (g1.match("b"));
	assert (!g1.match("aa"));
	assert (g1.match("."));

	Glob g2("\\?");
	assert (g2.match("?"));
	assert (!g2.match("a"));
	assert (!g2.match("ab"));

	Glob g3("a?");
	assert (g3.match("aa"));
	assert (g3.match("az"));
	assert (!g3.match("a"));
	assert (!g3.match("aaa"));

	Glob g4("??");
	assert (g4.match("aa"));
	assert (g4.match("ab"));
	assert (!g4.match("a"));
	assert (!g4.match("abc"));

	Glob g5("?a?");
	assert (g5.match("aaa"));
	assert (g5.match("bac"));
	assert (!g5.match("bbc"));
	assert (!g5.match("ba"));
	assert (!g5.match("ab"));

	Glob g6("a\\?");
	assert (g6.match("a?"));
	assert (!g6.match("az"));
	assert (!g6.match("a"));

	Glob g7("?", Glob::GLOB_DOT_SPECIAL);
	assert (g7.match("a"));
	assert (g7.match("b"));
	assert (!g7.match("aa"));
	assert (!g7.match("."));
}

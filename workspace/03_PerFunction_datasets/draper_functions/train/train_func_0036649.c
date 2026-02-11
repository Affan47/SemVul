getToken(Token wanted, const char* expected)
{
    Token t = nextToken();
    if (t != wanted) {
	if (t == T_LEXERR)
	    syntaxError("unmatched quote mark");
	else
	    syntaxError(fxStr::format("expecting %s", expected));
	return (false);
    } else
	return (true);
}

isLispoperator(char ch) {
	if (IsASCII(ch) && isalnum(ch))
		return false;
	if (ch == '\'' || ch == '`' || ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}')
		return true;
	return false;
}

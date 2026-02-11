process_attribute(int target)
{
	int brace = 0;
	int c;


	while ((c = nexttoken("()", c_reserved_word)) != EOF) {
		if (c == '(')
			brace++;
		else if (c == ')')
			brace--;
		else if (c == SYMBOL) {
			if (target == REF) {
				if (defined(token))
					PUT(token, lineno, sp);
			} else if (target == SYM) {
				if (!defined(token))
					PUT(token, lineno, sp);
			}
		}
		if (brace == 0)
			break;
	}
}

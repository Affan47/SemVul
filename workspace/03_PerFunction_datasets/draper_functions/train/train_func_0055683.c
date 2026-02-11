regoptail(regex_t *preg, int p, int val )
{

	if (p != 0 && OP(preg, p) == BRANCH) {
		regtail(preg, OPERAND(p), val);
	}
}

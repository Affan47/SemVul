parse_sum (g, cp, valp)
IfParser *g;
const char *cp;
long *valp;
{
    long rightval;

    DO (cp = parse_product (g, cp, valp));
    SKIPSPACE (cp);

    switch (*cp) {
      case '+':
	DO (cp = parse_sum (g, cp + 1, &rightval));
	*valp = (*valp + rightval);
	break;

      case '-':
	DO (cp = parse_sum (g, cp + 1, &rightval));
	*valp = (*valp - rightval);
	break;
    }
    return cp;
}

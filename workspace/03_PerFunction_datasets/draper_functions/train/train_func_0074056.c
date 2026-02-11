spitoption(const int arg, const int firstarg, FILE *xfl, const int	pch, const int cc)
{
	int	v = arg - firstarg;

	if  (optvec[v].isplus)
		fprintf(xfl, "%c+%s", pch, optvec[v].aun.string);
	else  if  (optvec[v].aun.letter == 0)
		fprintf(xfl, "%c+missing-arg-code-%d", pch, arg);
	else  if  (cc)  {
		fprintf(xfl, "%c", optvec[v].aun.letter);
		return  1;
	}
	else  {
		fprintf(xfl, "%c-%c", pch, optvec[v].aun.letter);
		return  1;
	}
	return  0;
}

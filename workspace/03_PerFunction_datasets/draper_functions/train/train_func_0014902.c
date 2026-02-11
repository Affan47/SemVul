verboseHLine(int n)
{
	docstring res;
	for (int i = 0; i < n; ++i)
		res += "\\hline";
	if (n)
		res += ' ';
	return res;
}

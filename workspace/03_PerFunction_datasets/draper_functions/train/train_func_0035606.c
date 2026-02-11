setIndent(int vl)
{
	if (vl < 0)
		vl = 1;
	if (vl >= 0 && vl <= 7 && vl != arrangement.indent)
	{
		arrangement.indent = vl;
		performArrange();
	}
}

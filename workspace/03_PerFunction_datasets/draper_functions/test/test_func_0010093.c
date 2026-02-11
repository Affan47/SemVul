follow(int expect, int ifyes, int ifno)
{
	int c = Bgetc(bin);

	if (c == expect)
		return ifyes;
	Bungetc(bin);
	return ifno;
}

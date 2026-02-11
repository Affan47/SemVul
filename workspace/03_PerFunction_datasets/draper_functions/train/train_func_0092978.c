MulInv(IDEA::Word x)
{
	IDEA::Word y=x;
	for (unsigned i=0; i<15; i++)
	{
		DirectMUL(y,low16(y));
		DirectMUL(y,x);
	}
	return low16(y);
}

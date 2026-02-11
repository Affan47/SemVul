padding()
{
    int n = deeper->ftell();
    n %= 4;
    if (n)
	deeper->skip(4 - n);
}

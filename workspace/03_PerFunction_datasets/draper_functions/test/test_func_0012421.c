hash(string substring, int m)
{
	int h = 0, a = 127;
	for(int i = 0; i < substring.length(); i++)
	{
		h = (a*h + (int)substring.at(i)) % m;
	}
	return h;
}

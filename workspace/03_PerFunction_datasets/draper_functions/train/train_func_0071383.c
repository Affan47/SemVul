additive()
{
	int Left = multiplicative();
	while (Pos < Text.length())
		if (Text[Pos] == '+')
		{
			++Pos;
			ws();
			int Right = multiplicative();
			Left += Right;
		}
		else if (Text[Pos] == '-')
		{
			++Pos;
			ws();
			int Right = multiplicative();
			Left -= Right;
		}
		else
			break;
	return Left;
}

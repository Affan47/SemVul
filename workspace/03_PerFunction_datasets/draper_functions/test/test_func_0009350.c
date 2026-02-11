computerDiceSelected()
{
	bool selected = false;
	int i = 0;
	while (!selected && i < 5)
	{
		selected = DiceValues[i].sel;
		i++;
	}
	return selected;
}

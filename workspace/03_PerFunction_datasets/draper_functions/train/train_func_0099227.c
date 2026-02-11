generateDices()
{
	bool any = false;
	for (int i = 0; i < 5; i++)
	{
		if (m_rollDice[i])
		{
			m_dice[i] = 1 + (int)(6.0 * KRandom::random() / (RAND_MAX + 1.0));
			m_rollDice[i] = false;
			any = true;
		}
	}
	return any;
}

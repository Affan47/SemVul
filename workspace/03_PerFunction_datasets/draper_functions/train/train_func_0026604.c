HiSax_shiftcards(int idx)
{
	int i;

	for (i = idx; i < (HISAX_MAX_CARDS - 1); i++)
		memcpy(&cards[i], &cards[i + 1], sizeof(cards[i]));
}

cards_deck_reset (CardsDeck *deck)
{
	gint i;
	Card *card;

	for (i = 0; i < deck->len; i++)
	{
		card = &g_array_index(deck, Card, i);
		card->drawn = FALSE;
		card->selected = FALSE;
		card->active = FALSE;
	}
}

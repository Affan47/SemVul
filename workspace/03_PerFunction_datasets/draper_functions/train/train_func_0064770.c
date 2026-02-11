initModel(Game *game)
{
	int i;
	for (i=0; i<MAX_ROUNDS; i++) {
		flopsBase[i].dealerRoot = NULL;
		flopsBase[i].nonDealerRoot = NULL;
	}
}

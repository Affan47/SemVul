towers_over (byte *board)
{
	return board [TOWERS_TOWER_WID/2] != TOWERS_RING_BOT &&
		board [TOWERS_TOWER_WID/2+TOWERS_TOWER_WID] != TOWERS_RING_BOT;
}

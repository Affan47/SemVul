start(const Board & board, const Clock & clock, int mode)
{
	Game game(board, clock, clock);
	game.start();
	start(game, mode, NO_COLOR);
}

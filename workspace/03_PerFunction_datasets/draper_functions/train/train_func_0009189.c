grid_test_7(int a1, int a2)
{
	COccupancyGridMap2D		gridmap(-20,20,-20,20, 0.05);
	CTicTac tictac;

	gridmap.resizeGrid(-30,30,-40,40);

	return tictac.Tac();
}

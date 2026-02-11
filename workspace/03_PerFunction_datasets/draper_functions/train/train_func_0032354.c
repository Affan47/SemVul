grid_test_2(int a1, int a2)
{
	COccupancyGridMap2D		gridMap(-20,20,-20,20, 0.05);


	const long N = 10000000;

	float	p=0.8f;

	CTicTac	 tictac;
	for (long i=0;i<N;i++)
	{
		gridMap.setCell( 0, 0, p );
	}
	return tictac.Tac()/N;
}

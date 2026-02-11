grid_test_8(int a1, int a2)
{
	randomGenerator.randomize(333);


	CObservation2DRangeScan	scan1;
	scan1.aperture = M_PIf;
	scan1.rightToLeft = true;
	scan1.validRange.resize( sizeof(SCAN_RANGES_1)/sizeof(SCAN_RANGES_1[0]) );
	scan1.scan.resize( sizeof(SCAN_RANGES_1)/sizeof(SCAN_RANGES_1[0]) );

	memcpy( &scan1.scan[0], SCAN_RANGES_1, sizeof(SCAN_RANGES_1) );
	memcpy( &scan1.validRange[0], SCAN_VALID_1, sizeof(SCAN_VALID_1) );

	COccupancyGridMap2D		gridmap(-20,20,-20,20, 0.05);


	const long N = 5000;

	CPose3D pose3D(0,0,0);
	gridmap.insertObservation( &scan1, &pose3D );

	double R = 0;
	CTicTac tictac;
	for (long i=0;i<N;i++)
	{
		CPose2D  pose(
			randomGenerator.drawUniform(-1.0,1.0),
			randomGenerator.drawUniform(-1.0,1.0),
			randomGenerator.drawUniform(-M_PI,M_PI) );
		R+=gridmap.computeObservationLikelihood(&scan1,pose);
	}
	return tictac.Tac()/N;
}

poses_test_compose3D2(int a1, int a2)
{
	const long N = 100000;
	CTicTac	 tictac;

	CPose3D a(1.0,2.0,3.0,DEG2RAD(10),DEG2RAD(50),DEG2RAD(-30));
	CPose3D b(8.0,-5.0,-1.0,DEG2RAD(-40),DEG2RAD(10),DEG2RAD(-45));

	CPose3D p;
	for (long i=0;i<N;i++)
	{
		p.composeFrom(a,b);
	}
	double T = tictac.Tac()/N;
	dummy_do_nothing_with_string( mrpt::format("%f",p.x()) );
	return T;
}

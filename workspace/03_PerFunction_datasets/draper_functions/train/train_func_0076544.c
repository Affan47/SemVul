poses_test_compose3DQuatpoint2(int a1, int a2)
{
	const long N = 500000;
	CTicTac	 tictac;

	CPose3DQuat  a(CPose3D(1.0,2.0,3.0,DEG2RAD(10),DEG2RAD(50),DEG2RAD(-30)));
	CPoint3D  b(8.0,-5.0,-1.0);

	double x,y,z;
	for (long i=0;i<N;i++)
	{
		a.composePoint(b.x(),b.y(),b.z(),x,y,z);
	}
	double T = tictac.Tac()/N;
	dummy_do_nothing_with_string( mrpt::format("%f",x) );
	return T;
}

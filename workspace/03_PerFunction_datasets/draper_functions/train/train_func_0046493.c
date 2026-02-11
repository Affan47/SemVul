test_composeAndInvComposePoint(
		double x1,double y1,double z1, double yaw1,double pitch1,double roll1,
		double x, double y, double z)
	{
		const CPose3DQuat q1(CPose3D(x1,y1,z1,yaw1,pitch1,roll1));
		TPoint3D pp(x,y,z), aux;
		q1.composePoint( x,y,z, pp.x,pp.y,pp.z);
		q1.inverseComposePoint( pp.x,pp.y,pp.z, aux.x, aux.y, aux.z );

		EXPECT_NEAR(x,aux.x, 1e-7);
		EXPECT_NEAR(y,aux.y, 1e-7);
		EXPECT_NEAR(z,aux.z, 1e-7);
	}

test_invComposePoint(double x1,double y1,double z1, double yaw1,double pitch1,double roll1,
	                 double x,double y,double z)
	{
		const CPose3D		p1(x1,y1,z1,yaw1,pitch1,roll1);
		const CPose3DQuat  	q1(p1);
		const CPoint3D  	p(x,y,z);

		CPoint3D  p_minus_p1 = p - p1;
		CPoint3D  p_minus_q1 = p - q1;

		CPoint3D  p_rec = q1 + p_minus_q1;


		EXPECT_NEAR(0, (p_minus_p1.getAsVectorVal()-p_minus_q1.getAsVectorVal()).array().abs().sum(), 1e-5) <<
			"p_minus_p1: " << p_minus_p1 << endl <<
			"p_minus_q1: " << p_minus_q1 << endl;

		EXPECT_NEAR(0, (p_rec.getAsVectorVal()-p.getAsVectorVal()).array().abs().sum(), 1e-5) <<
			"p_rec: " << p_rec << endl <<
			"p: " << p << endl;
	}

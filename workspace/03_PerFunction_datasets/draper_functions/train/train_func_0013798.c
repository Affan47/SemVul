test_fromYPRAndBack(double x1,double y1,double z1, double yaw1,double pitch1,double roll1)
	{
		const CPose3D p1(x1,y1,z1,yaw1,pitch1,roll1);
		const CPose3DQuat q1(p1);
		const CPose3D p1r = q1;

		EXPECT_NEAR(0, (p1.getHomogeneousMatrixVal()-q1.getHomogeneousMatrixVal()).array().abs().sum(), 1e-5) <<
			"p1.getHomogeneousMatrixVal():\n" << p1.getHomogeneousMatrixVal() << endl <<
			"q1.getHomogeneousMatrixVal():\n" << q1.getHomogeneousMatrixVal() << endl;

		EXPECT_NEAR(0, (p1.getAsVectorVal()-p1r.getAsVectorVal()).array().abs().sum(), 1e-5) <<
			"p1: " << p1 << endl <<
			"q1: " << q1 << endl <<
			"p1r: " << p1r << endl;
	}

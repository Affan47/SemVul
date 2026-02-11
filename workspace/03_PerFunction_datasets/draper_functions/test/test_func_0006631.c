test_compose(double x1,double y1,double z1, double yaw1,double pitch1,double roll1,
	                 double x2,double y2,double z2, double yaw2,double pitch2,double roll2 )
	{
		const CPose3D p1(x1,y1,z1,yaw1,pitch1,roll1);
		const CPose3D p2(x2,y2,z2,yaw2,pitch2,roll2);

		const CPose3D  p1_c_p2 = p1 + p2;
		const CPose3D  p1_i_p2 = p1 - p2;


		CPose3DQuat  q1=CPose3DQuat(p1);
		CPose3DQuat  q2=CPose3DQuat(p2);

		CPose3DQuat  q1_c_q2=q1+q2;
		CPose3DQuat  q1_i_q2=q1-q2;

		CPose3D p_q1_c_q2 = CPose3D(q1_c_q2);
		CPose3D p_q1_i_q2 = CPose3D(q1_i_q2);

		EXPECT_NEAR(0, (p1_c_p2.getAsVectorVal()-p_q1_c_q2.getAsVectorVal()).array().abs().sum(), 1e-5) <<
			"p1_c_p2: " << p1_c_p2 << endl <<
			"q1_c_p2: " << p_q1_c_q2 << endl;

		EXPECT_NEAR(0, (p1_i_p2.getAsVectorVal()-p_q1_i_q2.getAsVectorVal()).array().abs().sum(), 1e-5) <<
			"p1_i_p2: " << p1_i_p2 << endl <<
			"q1_i_p2: " << p_q1_i_q2 << endl;


		{
			CPose3DQuat C = q1;
			CPose3DQuat A = C + q2;
			EXPECT_NEAR(0, (A.getAsVectorVal()-q1_c_q2.getAsVectorVal()).array().abs().sum(), 1e-6);
		}

		{
			CPose3DQuat A = q1;
			A = A + q2;
			EXPECT_NEAR(0, (A.getAsVectorVal()-q1_c_q2.getAsVectorVal()).array().abs().sum(), 1e-6);
		}

		{
			CPose3DQuat A = q1;
			A += q2;
			EXPECT_NEAR(0, (A.getAsVectorVal()-q1_c_q2.getAsVectorVal()).array().abs().sum(), 1e-6);
		}

	}

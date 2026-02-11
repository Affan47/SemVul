testCompositionJacobian(
		double x,double y, double z, double yaw, double pitch, double roll,
		double x2,double y2, double z2, double yaw2, double pitch2, double roll2)
	{
		const CPose3DQuat  q1( CPose3D(x,y,z,yaw,pitch,roll) );
		const CPose3DQuat  q2( CPose3D(x2,y2,z2,yaw2,pitch2,roll2) );


		CMatrixDouble77  df_dx(UNINITIALIZED_MATRIX), df_du(UNINITIALIZED_MATRIX);
		CPose3DQuatPDF::jacobiansPoseComposition(
			q1,
			q2,
			df_dx,
			df_du );


		CMatrixDouble77  num_df_dx(UNINITIALIZED_MATRIX), num_df_du(UNINITIALIZED_MATRIX);
		{
			CArrayDouble<2*7> x_mean;
			for (int i=0;i<7;i++) x_mean[i]=q1[i];
			for (int i=0;i<7;i++) x_mean[7+i]=q2[i];

			double DUMMY=0;
			CArrayDouble<2*7> x_incrs;
			x_incrs.assign(1e-7);
			CMatrixDouble numJacobs;
			mrpt::math::jacobians::jacob_numeric_estimate(x_mean,func_compose,x_incrs, DUMMY, numJacobs );

			numJacobs.extractMatrix(0,0, num_df_dx);
			numJacobs.extractMatrix(0,7, num_df_du);
		}


		EXPECT_NEAR(0, (df_dx-num_df_dx).array().abs().sum(), 3e-3 )
			<< "q1: " << q1 << endl
			<< "q2: " << q2 << endl
			<< "Numeric approximation of df_dx: " << endl << num_df_dx << endl
			<< "Implemented method: " << endl << df_dx << endl
			<< "Error: " << endl << df_dx-num_df_dx << endl;

		EXPECT_NEAR(0, (df_du-num_df_du).array().abs().sum(), 3e-3 )
			<< "q1: " << q1 << endl
			<< "q2: " << q2 << endl
			<< "Numeric approximation of df_du: " << endl << num_df_du << endl
			<< "Implemented method: " << endl << df_du << endl
			<< "Error: " << endl << df_du-num_df_du << endl;
	}

poses_test_convert_quat_ypr_pdf(int a1, int a2)
{
	if (a1>=0)
		mrpt::global_settings::USE_SUT_QUAT2EULER_CONVERSION = a1!=0;

	const long N = 2000;

	CPose3D a_mean(1.0,2.0,3.0,DEG2RAD(10),DEG2RAD(50),DEG2RAD(-30));
	CMatrixDouble66 a_cov;
	{
		CMatrixFixedNumeric<double,6,8> v;
		mrpt::random::randomGenerator.randomize(1234);
		mrpt::random::randomGenerator.drawGaussian1DMatrix(v);
		v*=0.1;
		a_cov.multiply_AAt(v);
		for (int i=3;i<6;i++) a_cov(i,i)+=square(DEG2RAD(2.0));
	}
	CPose3DPDFGaussian a(a_mean,a_cov);

	CPose3DQuatPDFGaussian  b =CPose3DQuatPDFGaussian(a);

	double x;
	CTicTac	 tictac;
	for (long i=0;i<N;i++)
	{
		CPose3DPDFGaussian  q(b);
		x=q.mean.x();
	}
	double T = tictac.Tac()/N;
	dummy_do_nothing_with_string( mrpt::format("%f",x) );
	CPose3DPDFGaussian  q(b);

	return T;
}

testToQuatPDFAndBack(double x,double y, double z, double yaw, double pitch, double roll, double std_scale)
	{
		CPose3DPDFGaussian  p6pdf = generateRandomPose3DPDF(x,y,z,yaw,pitch,roll, std_scale);

		CPose3DQuatPDFGaussian  p7pdf = CPose3DQuatPDFGaussian(p6pdf);

		CPose3DPDFGaussian  p6pdf_recov = CPose3DPDFGaussian(p7pdf);


		const double val_mean_error = (p6pdf_recov.mean.getAsVectorVal() - p6pdf.mean.getAsVectorVal()).array().abs().mean();
		const double cov_mean_error = (p6pdf_recov.cov - p6pdf.cov).array().abs().mean();

		EXPECT_TRUE(val_mean_error < 1e-8);
		EXPECT_TRUE(cov_mean_error < 1e-8);
	}

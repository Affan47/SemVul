getAsPose2DForcingOrigin(const TPoint2D &origin,mrpt::poses::CPose2D &outPose) const	{
	if (!contains(origin)) throw std::logic_error("Base point is not contained in the line");
	outPose=mrpt::poses::CPose2D(TPose2D(origin));

	outPose.phi( atan2(coefs[0],-coefs[1]) );
}

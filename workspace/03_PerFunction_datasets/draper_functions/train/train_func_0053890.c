mahalanobisDistanceTo( const CPointPDFGaussian & other, bool only_2D  ) const
{

	CMatrixDouble13 deltaX;
	deltaX.get_unsafe(0,0) = other.mean.x() - mean.x();
	deltaX.get_unsafe(0,1) = other.mean.y() - mean.y();
	deltaX.get_unsafe(0,2) = other.mean.z() - mean.z();


	CMatrixDouble33 COV = other.cov;
	COV += this->cov;

	if (!only_2D)
	{
		CMatrixDouble33 COV_inv;
		COV.inv(COV_inv);
		return sqrt( deltaX.multiply_HCHt_scalar(COV_inv) );
	}
	else
	{
		CMatrixDouble22 C = COV.block(0,0,2,2);
		CMatrixDouble22 COV_inv;
		C.inv(COV_inv);
		CMatrixDouble12 deltaX2 = deltaX.block(0,0,1,2);
		return std::sqrt( deltaX2.multiply_HCHt_scalar(COV_inv) );
	}


}

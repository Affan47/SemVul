operator==(const CPose3DQuatPDFGaussianInf &p1,const CPose3DQuatPDFGaussianInf &p2)
{
	return p1.mean==p2.mean && p1.cov_inv==p2.cov_inv;
}

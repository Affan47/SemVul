bayesianFusion(const  CPosePDF &p1_,const  CPosePDF &p2_, const double &minMahalanobisDistToDrop )
{
	MRPT_START

	MRPT_UNUSED_PARAM(minMahalanobisDistToDrop);


	ASSERT_( p1_.GetRuntimeClass() == CLASS_ID(CPosePDFSOG) );
	ASSERT_( p2_.GetRuntimeClass() == CLASS_ID(CPosePDFGaussian) );

	const CPosePDFSOG			*p1 = static_cast<const CPosePDFSOG*>(&p1_);
	const CPosePDFGaussian		*p2 = static_cast<const CPosePDFGaussian*>(&p2_);


	CPosePDFGaussian	auxGaussianProduct,auxSOG_Kernel_i;

	CMatrixDouble33	covInv;
	p2->cov.inv(covInv);

	CMatrixDouble31	eta = CMatrixDouble31(p2->mean);
	eta = covInv * eta;


	double				a = -0.5*( 3*log(M_2PI) - log( covInv.det() ) + (eta.adjoint() * p2->cov * eta)(0,0) );

	this->m_modes.clear();
	for (const_iterator it =p1->m_modes.begin();it!=p1->m_modes.end();++it)
	{
		auxSOG_Kernel_i.mean = (it)->mean;
		auxSOG_Kernel_i.cov  = CMatrixDouble( (it)->cov );
		auxGaussianProduct.bayesianFusion( auxSOG_Kernel_i, *p2 );


		TGaussianMode		newKernel;
		newKernel.mean = auxGaussianProduct.mean;
		newKernel.cov  = auxGaussianProduct.cov;

		CMatrixDouble33	covInv_i;
		auxSOG_Kernel_i.cov.inv(covInv_i);

		CMatrixDouble31	eta_i = CMatrixDouble31(auxSOG_Kernel_i.mean);
		eta_i = covInv_i * eta_i;

		CMatrixDouble33 new_covInv_i;
		newKernel.cov.inv(new_covInv_i);

		CMatrixDouble31	new_eta_i = CMatrixDouble31(newKernel.mean);
		new_eta_i = new_covInv_i * new_eta_i;

		double		a_i	    = -0.5*( 3*log(M_2PI) - log( new_covInv_i.det() ) + (eta_i.adjoint() * auxSOG_Kernel_i.cov * eta_i)(0,0) );
		double		new_a_i = -0.5*( 3*log(M_2PI) - log( new_covInv_i.det() ) + (new_eta_i.adjoint() * newKernel.cov * new_eta_i)(0,0) );


		newKernel.log_w	   = (it)->log_w + a + a_i - new_a_i;


		this->m_modes.push_back(newKernel );
	}

	normalizeWeights();

	MRPT_END
}

getEigenValues(Vector& eig) const
{
	int d_size = getSize();
	if (eig.length() != 2*d_size) {
		char mes[500];
		sprintf(mes, "Wrong length of vector for eigenvalues len=%d, should be=%d.\n",
				eig.length(), 2*d_size);
		throw SYLV_MES_EXCEPTION(mes);
	}
	for (const_diag_iter it = begin(); it != end(); ++it) {
		const DiagonalBlock& b = *it;
		int ind = b.getIndex();
		eig[2*ind] = *(b.getAlpha());
		if (b.isReal()) {
			eig[2*ind+1] = 0.0;
		} else {
			double beta = sqrt(b.getSBeta());
			eig[2*ind+1] = beta;
			eig[2*ind+2] = eig[2*ind];
			eig[2*ind+3] = -beta;
		}
	}
}

make_js_covariance_matrix(vector<ublas::matrix<double> >& kappa_covariances,
							   ublas::matrix<double>& js_covariance)
{
	size_t kappa_length = 0;
	for (size_t i = 1; i < kappa_covariances.size(); ++i)
	{
		assert (kappa_covariances[i].size1() == kappa_covariances[i-1].size1());
		assert (kappa_covariances[i].size2() == kappa_covariances[i-1].size2());

		kappa_length = kappa_covariances[i].size1();
	}

	if (kappa_length == 0)
		return;

	js_covariance = ublas::zero_matrix<double>(kappa_covariances.size() * kappa_length,
											   kappa_covariances.size() * kappa_length);
	for (size_t i = 0; i < kappa_covariances.size(); ++i)
	{
		for (size_t j = 0; j < kappa_length; ++j)
		{
			for (size_t k = 0; k < kappa_length; ++k)
			{
				js_covariance(i*kappa_length + j, i*kappa_length + k) =
				kappa_covariances[i](j,k);
                assert (!isinf(js_covariance(i*kappa_length + j, i*kappa_length + k) && ! isnan(js_covariance(i*kappa_length + j, i*kappa_length + k))));
			}
		}
	}
}

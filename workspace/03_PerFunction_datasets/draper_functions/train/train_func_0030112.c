evaluate(double *value,  vector<double const *> const &args,
		       vector<unsigned int> const &lengths) const
    {
	double ans = *max_element(args[0], args[0] + lengths[0]);
	for (unsigned int i = 1; i < args.size(); ++i) {
	    double maxi = *max_element(args[i], args[i] + lengths[i]);
	    ans = max(ans, maxi);
	}
	*value = ans;
    }

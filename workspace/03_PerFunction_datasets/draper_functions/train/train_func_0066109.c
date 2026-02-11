checkArgs(vector<double const *> const &args) const
    {
	vector<double const *> param(_dist->npar());
	for (unsigned int i = 0; i < param.size(); ++i) {
	    param[i] = args[i+1];
	}

	return _dist->checkParameterValue(param);
    }
}

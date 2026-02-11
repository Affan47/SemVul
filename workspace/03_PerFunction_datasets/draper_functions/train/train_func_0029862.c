evaluate(vector<double const *> const &args) const
    {
	return *args[0] ? *args[1] : *args[2];
    }

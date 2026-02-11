checkScalarValue (vector <double const *> const &args) const
    {
	double p = *args[0];
	return (p > 0 && p < 1);
    }

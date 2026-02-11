Initialise(const vector<Real>& X, const vector<Complex>& Y)
{
    int i;
    n = X.size();
    if (n != (int)Y.size())
	throw "ERROR in AbstractInterpolator::Initialise: \
X and Y have different sizes";
    for (i=1; i<n; i++)
    {
	if (X[i-1] >= X[i]) throw "ERROR in AbstractInterpolator::Initialise: \
'X' must be sorted in the ascending order";
    }
    X_copy = new Real[n];
    Y_copy = new Complex[n];
    for (i=0; i<n; i++)
    {
	X_copy[i] = X[i];
	Y_copy[i] = Y[i];
    }
}

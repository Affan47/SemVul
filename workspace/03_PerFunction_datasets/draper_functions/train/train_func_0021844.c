initialize(unsigned int n)
{

    if (isInitialized(this, n))
        return true;


    for (unsigned int i = 0; i < _parents.size(); ++i) {
        if (!isInitialized(_parents[i], n)) {
	    return false;
        }
    }

    deterministicSample(n);

    return true;
}

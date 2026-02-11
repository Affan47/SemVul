resize(int nn, void *e)
{
    if (nn <= _capacity || reserve(nn)) {
	for (int i = _n; i < nn; i++)
	    _l[i] = e;
	_n = nn;
    }
}

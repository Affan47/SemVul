rescale(double p)
{
    ++_n;
    p = min(p, 1.0);
    _sump += p;

    if (_n % N_REFRESH == 0) {

	_meanp = _sump / N_REFRESH;
	_sump = 0;
    }

    if (_n_isotonic == 0) {


	_lstep += (p - 0.234) / _nstep;
	if ((p > 0.234) != _p_over_target) {
	    _p_over_target = !_p_over_target;
	    ++_nstep;
	}


	if (_n % N_REFRESH == 0 && _meanp >= 0.15 && _meanp <= 0.35) {
	    _n_isotonic = _n;
	    _nstep = 100;
	}
    }
    else {

	_lstep += (p - 0.234) / sqrt(static_cast<double>(_nstep));
        _nstep++;


	unsigned int N = _gv->length();
	double const *x = _gv->nodes()[0]->value(_chain);
	for (unsigned int i = 0; i < N; ++i) {
	    _mean[i] += 2 * (x[i] - _mean[i]) / (_n - _n_isotonic + 1);
	}
	for (unsigned int i = 0; i < N; ++i) {
	    for (unsigned int j = 0; j < N; ++j) {
		_var[i + N * j] += 2 * ((x[i] - _mean[i]) *
					    (x[j] - _mean[j]) -
					    _var[i + N * j]) / _n;
	    }
	}
    }
}

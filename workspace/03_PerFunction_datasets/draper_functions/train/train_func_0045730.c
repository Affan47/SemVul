update(double z, double n, RNG *rng)
    {

	if (n != _nlast) {
	    updateN(n);
	}

	vector<double> p(_ncomp);

	double maxp = 0;
	for (int i = 0; i < _ncomp; i++) {
	    p[i] = dnorm(z, _means[i], sqrt(_variances[i]), true) +
		log(_weights[i]);
	    if (i == 0 || p[i] > maxp)
		maxp = p[i];
	}


	double sump = 0;
	for (int i = 0; i < _ncomp; i++) {
	    p[i] = sump + exp(p[i] - maxp);
	    sump = p[i];
	}


	double u = rng->uniform() * sump;
	for (_r = 0; _r < _ncomp - 1; _r++) {
	    if (u < p[_r]) {
		break;
	    }
	}
    }

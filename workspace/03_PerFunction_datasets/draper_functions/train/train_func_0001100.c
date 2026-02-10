getValue(unsigned int i) const
    {
	Node const *child = _view->stochasticChildren()[i];

	double y = child->value(_chain)[0];
	if (_family[i] == GLM_BINOMIAL) {
	    double N = child->parents()[1]->value(_chain)[0];
	    y /= N;
	}

	if (_link[i] == 0) {
	    return y;
	}
	else {
	    double mu = _link[i]->value(_chain)[0];
	    double eta = _link[i]->eta(_chain);
	    double grad = _link[i]->grad(_chain);

	    return eta + (y - mu) / grad;
	}
    }

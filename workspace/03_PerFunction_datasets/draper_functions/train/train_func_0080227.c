update(RNG *rng)
{
    vector<double> value(length());
    unsigned int nrow = _dsnode->length();
    unsigned int ncol = _gv->nodes().size();
    unsigned int nrep = nrow * (ncol - 1);

    for (unsigned int j = 0; j < nrep; ++j) {
	double log_p = -_gv->logFullConditional(_chain);
	getValue(value);
	step(value, nrow, ncol, _step_adapter.stepSize(), rng);
	setValue(value);
	log_p += _gv->logFullConditional(_chain);
	accept(rng, exp(log_p));
    }
}

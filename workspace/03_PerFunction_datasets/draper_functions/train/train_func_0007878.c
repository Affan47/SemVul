WriteOutput(MonitorControl const &control, int chain,
			ofstream &output)
{
    Monitor const *monitor = control.monitor();
    if (monitor->poolIterations()) {
	return;
    }

    vector<double> const &y = monitor->value(chain);
    unsigned int nvar = product(monitor->dim());
    for (unsigned int offset = 0; offset < nvar; ++offset) {
	unsigned int iter = control.start();
	for (unsigned int k = 0; k < control.niter(); ++k) {
	    output << iter << "  ";
	    writeDouble(y[k * nvar + offset], output);
	    output << '\n';
	    iter += control.thin();
	}
    }
}

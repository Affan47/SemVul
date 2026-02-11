WriteIndex(MonitorControl const &control,
		       ofstream &index, unsigned int &lineno)
{


    Monitor const *monitor = control.monitor();
    if (monitor->poolIterations()) {
	return;
    }

    unsigned int nvar = product(monitor->dim());
    vector<string> const &enames = monitor->elementNames();
    for (unsigned int i = 0; i < nvar; ++i) {
	index << enames[i] << " " << lineno + 1 << " "
	      << lineno + control.niter() << '\n';
	lineno += control.niter();
    }
}

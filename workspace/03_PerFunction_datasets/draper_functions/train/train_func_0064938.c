configure(Vector<String> &conf, ErrorHandler *errh)
{
    if (conf.size() != noutputs())
	return errh->error("need %d arguments, one per output port", noutputs());

    int before = errh->nerrors();
    Classification::Wordwise::Program prog = empty_program(errh);
    parse_program(prog, conf, errh);

    if (errh->nerrors() == before) {
	prog.warn_unused_outputs(noutputs(), errh);
	_prog = prog;
	return 0;
    } else
	return -1;
}

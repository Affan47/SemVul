parseOptionArg(bool inmainargs, const string& optionname, int argidx, CmdLineOption** cropt_p) {
	if (inmainargs) {
		cerr << ">> Options should come before " << m_MainArgType << " arguments" << endl;
		m_Error = 1;
		return false;
	}
	CmdLineOption* cropt = *cropt_p;
	if (cropt != NULL) {
		if (argidx < cropt->getMinNbArgs()) {
			cerr << ">> Option '" << cropt->getName() << "' requires "
			     << cropt->getMinNbArgs() << " arguments" << endl;
			m_Error = 1;
			return false;
		}

		for (int i = argidx; i < cropt->getMaxNbArgs(); i++) {
			cropt->getArg(i)->setDefaultValue();
		}
	}
	cropt = *cropt_p = getOption(optionname);
	if (cropt == NULL) {
		cerr << ">> Unknown option '" << getOptionPrefix() << optionname << "'" << endl;
		m_Error = 1;
		return false;
	} else {
		cropt->setHasOption(true);
	}
	return true;
}

addSPairListOption(const char* name, int id) {
	CmdLineOption* opt = new CmdLineOption(name);
	CmdLineArgSPairList* arg = new CmdLineArgSPairList(name);
	opt->addArg(arg);
	addOption(opt, id);
	return arg;
}

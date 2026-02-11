init_installed_versions(CmdLineObj& cmdline, ConfigCollection* collection) {
	CmdLineArgSet* versions = (CmdLineArgSet*)cmdline.getOption(GLE_OPT_VERSION)->getArg(0);
	ConfigSection* gle = collection->getSection(GLE_CONFIG_GLE);
	CmdLineArgSPairList* installs = (CmdLineArgSPairList*)gle->getOption(GLE_CONFIG_GLE_INSTALL)->getArg(0);
	if (installs->size() == 0) {
		versions->addPossibleValue("no older GLE versions found (run \"gle -finddeps\")");
	} else {
		for (int i = 0; i < installs->size(); i++) {
			versions->addPossibleValue(installs->getValue1(i).c_str());
		}
	}
}

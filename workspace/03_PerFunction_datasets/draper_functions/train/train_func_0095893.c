validate(std::string& err) {
	if (enumerate.mode == enum_bt && enumerate.restartOnModel) {
		err = "Options 'restart-on-model' and 'enum-mode=bt' are mutually exclusive!";
		return false;
	}
	for (uint32 i = 0; i != numSolvers(); ++i) {
		if (!validate(*getSolver(i), err)) { return false; }
	}
	return true;
}

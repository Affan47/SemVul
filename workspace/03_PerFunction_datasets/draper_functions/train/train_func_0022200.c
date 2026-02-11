findParameter(const string& name) {
	for (int i = 0; i < getNbParam(); i++) {
		if (str_i_equals(name, getParamNameShort(i))) {
			return i;
		}
	}
	return -1;
}

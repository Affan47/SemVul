tryLoad() {

	ifstream input;
	input.open(getLocation()->getFullPath().c_str());
	if (!input.is_open()) {
		return false;
	}
	load(input);
	input.close();
	return true;
}

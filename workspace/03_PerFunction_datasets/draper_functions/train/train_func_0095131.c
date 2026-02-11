xerror_string(XErrorEvent *error) {
	int index = -1;
	if (error) {
		index = (int) error->error_code;
	}
	if (0 <= index && index <= xerrors_max) {
		return xerrors[index];
	} else {
		return xerrors[xerrors_max+1];
	}
}

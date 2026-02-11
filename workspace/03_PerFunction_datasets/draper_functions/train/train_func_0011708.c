toString() const {
	std::string s = (!token) ? std::string("") : std::string("line(")+getLine()+"), ";
	s += getErrorMessage();
	return s;
}

operator>>( std::istream& input, Point& P) {
	char c;
	input >> c;
	input >> P.x;
	input >> c;
	if (c == ')') {
		P.setdim(1);
		return input;
	}

	input >> P.y;
	input >> c;
	if (c == ')') {
		P.setdim(2);
		return input;
	}

	input >> P.z;
	P.setdim(3);
	input >> c;
	return input;
}

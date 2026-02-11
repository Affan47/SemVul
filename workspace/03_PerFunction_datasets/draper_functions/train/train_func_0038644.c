update(const std::string&) {
	if (_sequence == 0)
		_sequence = 1;
	else if (_sequence == 1 && !World::menu())
		_sequence = 2;
}

update(const std::string& messages) {
	if (messages.find(MOVE_WHERE_TO_GO) != std::string::npos) {
		_last_target = _target.coordinate();
		_travel_target = Command(World::cursorMoves(World::cursor(), _target.coordinate()) + ".", PRIORITY_CONTINUE_ACTION);
		_sequence = 1;
	} else {
		_sequence = 2;
	}
}

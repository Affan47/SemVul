update(const std::string& messages) {
	if (messages.find(MESSAGE_WHAT_TO_APPLY) != std::string::npos) {
		_sequence = 1;
	} else if (messages.find(MESSAGE_IN_WHAT_DIRECTION) != std::string::npos) {
		_sequence = 2;
	} else if (messages.find(MESSAGE_UNLOCK_IT) != std::string::npos) {
		_sequence = 3;
	} else if (_sequence == 3) {
		_sequence = 4;
	} else {
		failed();
		_sequence = 4;
	}
}

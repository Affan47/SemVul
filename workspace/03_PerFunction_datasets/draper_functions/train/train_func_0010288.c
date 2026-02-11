clone() const {
		SimpleSASLContext* s = new SimpleSASLContext(provider());

		return s;
	}

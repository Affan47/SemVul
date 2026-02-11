skip(unsigned num, const std::string& reason) throw ()  {
		for(unsigned i = 0; i < num; ++i) {
			pass(" # skip " + reason);
		}
	}

clear() {
		for (size_t i = 0; i != c_.size(); ++i) {
			delete c_[i].array;
			delete c_[i].pars;
		}
		c_.clear();
	}

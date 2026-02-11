setState(vector<int> const &state)
    {
	if (state.size() != 3)
	    return false;

	for (unsigned int i = 0; i < 3; ++i) {
	    I[i] = static_cast<unsigned int>(state[i]);
	}
	fixupSeeds();
	return true;
    }

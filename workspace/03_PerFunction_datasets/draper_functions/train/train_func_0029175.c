setState(vector<int> const &state)
    {
	if (state.size() != 2)
	    return false;

	I[0] = static_cast<unsigned int>(state[0]);
	I[1] = static_cast<unsigned int>(state[1]);
	fixupSeeds();
	return true;
    }
